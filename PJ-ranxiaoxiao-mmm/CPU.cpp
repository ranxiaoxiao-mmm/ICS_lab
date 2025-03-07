#include<iostream>
#include<fstream>
#include<cstdint>
#include<vector>
#include<sstream>
#include<string>
#include<iomanip>

#include "CPU.h"

using namespace std;

int main(){
    CPU cpu;
    cpu.run();
    return 0;
}

//重置每条指令的局部变量
void CPU::reset(){
    ALU_A = 0;
    ALU_B = 0; 
    ALU_function = 0;

    address = 0;
    data = 0;
}

void CPU::run(){
    input();
    while(Stat == AOK){
        fetch();
        decode();
        execute();
        memory();
        writeback();
        update_PC();
        print();
        reset();
    }
}

bool CPU::judge_in(vector<uint8_t> check_list){
    for(size_t i = 0;i < check_list.size(); i++){
        if(icode == check_list[i]){
            return true;
        }
    }
    return false;
} //匹配判断操作符是否合法





//输入.yo文件
void CPU::input(){
    string line;
    while (getline(cin, line)) {
        if (line.empty() || line[0] == '|') continue; // 跳过空行和注释行

        stringstream ss(line);
        string address, instruction, comment;
        ss >> address >> instruction;
        getline(ss, comment, '#');

        try {
            // 解析地址
            uint64_t addr = stoull(address, nullptr, 16);

            // 解析指令
            for (size_t i = 0; i < instruction.size(); i += 2) {
                string byteStr = instruction.substr(i, 2);
                uint8_t byte = static_cast<uint8_t>(stoul(byteStr, nullptr, 16));
                Memory[addr + i / 2] = byte;
            }
        } catch (const invalid_argument& e) {
            // cerr << "无效的输入: " << line << endl;
            continue;
        } catch (const out_of_range& e) {
            // cerr << "输入超出范围: " << line << endl;
            continue;
        }
    }
}





//fetch
void CPU::fetch(){
    SC.imem_error = (PC >= MAXSIZE);
    if(SC.imem_error){
        icode = nop_code;
        ifun = 0;
    }
    else{
        icode = r_icode(Memory[PC]);
        ifun = r_ifun(Memory[PC]);
        SC.instr_valid = InsValid();
    }

    vector<uint8_t> read_reg = {rrmovq_code, irmovq_code, rmmovq_code, mrmovq_code, opq_code, pushq_code, popq_code, iopq_code};
    vector<uint8_t> read_valC = {irmovq_code, rmmovq_code, mrmovq_code, jxx_code, call_code, iopq_code};

    bool reg_read = judge_in(read_reg);
    bool valC_read = judge_in(read_valC); 

    if(reg_read && valC_read){
        rA = r_rA(Memory[PC + 1]);
        rB = r_rB(Memory[PC + 1]);
        valC = r_value(PC + 2);
        valP = PC + 10;
    }
    else if(reg_read){
        rA = r_rA(Memory[PC + 1]);
        rB = r_rB(Memory[PC + 1]);
        valP = PC + 2;
    }
    else if(valC_read){
        valC = r_value(PC + 1);
        valP = PC + 9;
    }
    else{
        valP = PC + 1;
    }
    //cout<<(int)icode<<" "<<(int)ifun<<" "<<(int)rA<<" "<<(int)rB<<" "<<valC<<" "<<valP<<endl; //----> 测试
    
}

uint8_t CPU::r_icode(uint8_t first_bytes){
    return (first_bytes&0xf0) >> 4;
}

uint8_t CPU::r_ifun(uint8_t first_bytes){
    return first_bytes & 0xf;
}

uint8_t CPU::r_rA(uint8_t second_bytes){
    return (second_bytes & 0xf0) >> 4;
}

uint8_t CPU::r_rB(uint8_t second_bytes){
    return second_bytes & 0xf;
}

uint64_t CPU::r_value(uint64_t other_bytes){
    uint64_t value = 0;
    for(int i = 0; i < 8; i++){
        value |= ((uint64_t)Memory[other_bytes + i]) << (i * 8);
    }
    return value;
} //取值

bool CPU::InsValid(){
    vector<uint8_t> j_and_m = {jxx_code, rrmovq_code}; //ifun != 0 jmp & cmov
    vector<uint8_t> op_alu = {opq_code};
    vector<uint8_t> other = {halt_code, nop_code, irmovq_code, rmmovq_code, mrmovq_code, call_code, ret_code, pushq_code, popq_code}; //ifun == 0

    if(icode > iopq_code){
        return true;
    }
    else if(judge_in(j_and_m) && ifun > g_code){
        return true;
    }
    else if(judge_in(op_alu) && ifun > remq_code){
        return true;
    }
    else if(judge_in(other) && ifun != 0){
        return true;
    }
    else{
        return false;
    }
} //判断指令是否合法





//decode
void CPU::decode(){
    w_srcA();
    w_srcB();
    w_dstE();
    w_dstM();
    //取值
    valA = Reg[srcA];
    valB = Reg[srcB];
    // cout<<(int)srcA<<" "<<(int)srcB<<" "<<(int)dstE<<" "<<(int)dstM<<" "<<valA<<" "<<valB<<endl;; //----> 测试
}

void CPU::w_srcA(){
    vector<uint8_t> srcA_set = {rrmovq_code, rmmovq_code, opq_code, pushq_code};
    vector<uint8_t> srcA_rsp = {popq_code, ret_code};
    if(judge_in(srcA_set)){
        srcA = rA;
    }
    else if(judge_in(srcA_rsp)){
        srcA = rsp_code;
    }
    else{
        srcA = reg_invalid_code;
    }
}

void CPU::w_srcB(){
    vector<uint8_t> srcB_set = {rmmovq_code, mrmovq_code, opq_code, iopq_code};
    vector<uint8_t> srcB_rsp = {pushq_code, popq_code, call_code, ret_code};
    if(judge_in(srcB_set)){
        srcB = rB;
    }
    else if(judge_in(srcB_rsp)){
        srcB = rsp_code;
    }
    else{
        srcB = reg_invalid_code;
    }
}

void CPU::w_dstE(){
    vector<uint8_t> dstE_set = {rrmovq_code, irmovq_code, opq_code, iopq_code};
    vector<uint8_t> dstE_rsp = {pushq_code, popq_code, call_code, ret_code};
    if(judge_in(dstE_set)){
        dstE = rB;
    }
    else if(judge_in(dstE_rsp)){
        dstE = rsp_code;
    }
    else{
        dstE = reg_invalid_code;
    }
}

void CPU::w_dstM(){
    vector<uint8_t> dstM_set = {mrmovq_code, popq_code};
    if(judge_in(dstM_set)){
        dstM = rA;
    }
    else{
        dstM = reg_invalid_code;
    }
}





//execute
void CPU::execute(){
    r_ALU_A();
    r_ALU_B();

    if(icode == opq_code){
        ALU_function = ifun;
    }
    else if(icode == iopq_code){
        ALU_function = ifun;
    }
    else{
        ALU_function = add_code;
    }
    ALU_calc(ALU_A, ALU_B, ALU_function);
    
    if(icode == opq_code){
        CC.cc_valid = true;
    }
    else if(icode == iopq_code){
        CC.cc_valid = true;
    }
    else{
        CC.cc_valid = false;
    }

    cnd = condition();
    if(icode == cmov_code && !cnd){ //条件mov但是条件不满足
        dstE = reg_invalid_code;    
    }
}

void CPU::r_ALU_A(){
    vector<uint8_t> A_valA = {rrmovq_code, opq_code};
    vector<uint8_t> A_valC = {irmovq_code, rmmovq_code, mrmovq_code, iopq_code};
    vector<uint8_t> A_rsp_sub8 = {call_code, pushq_code};
    vector<uint8_t> A_rsp_add8 = {ret_code, popq_code};
    if(judge_in(A_valA)){
        ALU_A = valA;
    }
    else if(judge_in(A_valC)){
        ALU_A = valC;
    }
    else if(judge_in(A_rsp_sub8)){
        ALU_A = -8;
    }
    else if(judge_in(A_rsp_add8)){
        ALU_A = 8;
    }
    else{
        ALU_A = 0;
    }
}

void CPU::r_ALU_B(){
    vector<uint8_t> B_valB = {rmmovq_code, mrmovq_code, pushq_code, popq_code, call_code, ret_code, opq_code, iopq_code};
    // vector<uint8_t> B_val0 = {rrmovq_code, rmmovq_code};
    if(judge_in(B_valB)){
        ALU_B = valB;
    }
    // else if(judge_in(B_val0)){
    //     ALU_B = 0;
    // }
    else{
        ALU_B = 0;
    }
}

void CPU::ALU_calc(uint64_t A, uint64_t B, uint8_t function){
    switch(function){
        case add_code:
            valE = B + A;
            break;
        case sub_code:
            valE = B - A;
            break;
        case and_code:
            valE = B & A;
            break;
        case xor_code:
            valE = B ^ A;
            break;
        //扩展
        case or_code:
            valE = B | A;
            break;
        case shl_code:
            valE = B << A;
            break;
        case shr_code:
            valE = B >> A;
            break;
        case sar_code:
            valE = (int64_t)B >> A;
            break;
        case mulq_code:
            valE = B * A;
            break;
        case divq_code:
            valE = B / A;
            break;
        case remq_code:
            valE = B % A;
            break;
        default:
            valE = UINT64_MAX; //返回错误值
            break;
    }
}

bool CPU::condition(){
    if(CC.cc_valid){
        CC.ZF = (valE == 0);
        CC.SF = (valE >> 63) & 1;
        bool A_sign = (ALU_A >> 63) & 1;
        bool B_sign = (ALU_B >> 63) & 1;

        if (ALU_function == add_code) {
            CC.OF = (A_sign == B_sign) && (CC.SF != A_sign);
        }
        else if (ALU_function == sub_code) {
            CC.OF = (A_sign != B_sign) && (CC.SF != B_sign);
        }
        else if(ALU_function == shl_code){
            CC.OF = (ALU_A & (1ULL << (63 - ALU_B))) != 0;
        }
        else {
            CC.OF = false;
        }
    }

    switch(ifun){
        case nonc_code:
            return true;
        case le_code:
            return CC.SF ^ CC.OF || CC.ZF;
        case l_code:
            return CC.SF ^ CC.OF;
        case e_code:
            return CC.ZF;
        case ne_code:
            return !CC.ZF;
        case ge_code:
            return !(CC.SF ^ CC.OF);
        case g_code:
            return !(CC.SF ^ CC.OF) && !CC.ZF;
        default:
            return false;
    }
}





//memory
void CPU::memory(){
    r_address();
    r_data();
    vector<uint8_t> read_valid = {mrmovq_code, popq_code, ret_code};
    vector<uint8_t> write_valid = {rmmovq_code, pushq_code, call_code};
    if(judge_in(read_valid)){
        read(address);
    }
    else if(judge_in(write_valid)){
        write(address, data);
    }
    w_stat();
    Stat = SC.new_stat; //更新CPU状态
}

void CPU::r_address(){
    vector<uint8_t> address_valE = {rmmovq_code, mrmovq_code, pushq_code, call_code};
    vector<uint8_t> address_valA = {popq_code, ret_code};
    if(judge_in(address_valE)){
        address = valE;
    }
    else if(judge_in(address_valA)){
        address = valA;
    }
    else{
        address = UINT64_MAX;
    }
}

void CPU::r_data(){
    vector<uint8_t> data_valA = {rmmovq_code, pushq_code};
    vector<uint8_t> data_valP = {call_code};
    if(judge_in(data_valA)){
        data = valA;
    }
    else if(judge_in(data_valP)){
        data = valP;
    }
    else{
        data = 0;
    }
}

void CPU::read(uint64_t addr){
    if(addr + 8 > MAXSIZE){
        SC.dmem_error = true;
    }
    else{
        valM = 0; //初始化，便于后续|=操作
        for(int i = 0; i < 8; i++){
            valM |= (uint64_t)Memory[addr + i] << (i * 8); //每次取一个字节
        }
        SC.dmem_error = false;
    }
}

void CPU::write(uint64_t addr, uint64_t data){
    if(addr + 8 > MAXSIZE || (((addr>>63)&1) == 1)){ //地址越界
        SC.dmem_error = true;
    }
    else{
        for(int i = 0; i < 8; i++){
            Memory[addr + i] = (data >> (i * 8)) & 0xff;
        }
        SC.dmem_error = false;
    }
}

void CPU::w_stat(){
    if(SC.imem_error || SC.dmem_error){
        SC.new_stat = ADR;
    }
    else if(SC.instr_valid){
        SC.new_stat = INS;
    }
    else if(icode == halt_code){
        SC.new_stat = HLT;
    }
    else{
        SC.new_stat = AOK;
    }
}





//writeback
void CPU::writeback(){
    if(dstE != reg_invalid_code && Stat == AOK){
        Reg[dstE] = valE;
    }
    if(dstM != reg_invalid_code && Stat == AOK){
        Reg[dstM] = valM;
    }
}





//update_PC
void CPU::update_PC(){
    w_PC();
    if(Stat == AOK){
        PC = refresh_PC;
    }
}

void CPU::w_PC(){
    if(icode == jxx_code && cnd){
        refresh_PC = valC;
    }
    else if(icode == call_code){
        refresh_PC = valC;
    }
    else if(icode == ret_code){
        refresh_PC = valM;
    }
    else{
        refresh_PC = valP;
    }
}





//输出到.yml文件
void CPU::print(){
    cout << "- PC: " << PC << endl;
    cout << "  REG:" << endl;
    for (int i = 0; i < 15; ++i) {
        cout << "    " << reg_name[i] << ": " << (long long)Reg[i] << endl;
    }
    cout << "  CC:" << endl;
    cout << "    ZF: " << CC.ZF << endl;
    cout << "    SF: " << CC.SF << endl;
    cout << "    OF: " << CC.OF << endl;
    cout << "  MEM:" << endl;
    for (int i = 0; i < MAXSIZE; i += 8) {
        int64_t value = *reinterpret_cast<int64_t*>(&Memory[i]);
        if (value != 0) {
            cout << "    " << i << ": " << value << endl;
        }
    }
    cout << "  STAT: " << static_cast<int>(Stat) << endl;

}

