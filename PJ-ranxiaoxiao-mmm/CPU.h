#ifndef CPU_H
#define CPU_H

#include<cstdint>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

//内存值
const int MAXSIZE = 1024;

//寄存器编码
const uint8_t rax_code = 0;
const uint8_t rcx_code = 1;
const uint8_t rdx_code = 2;
const uint8_t rbx_code = 3;
const uint8_t rsp_code = 4;
const uint8_t rbp_code = 5;
const uint8_t rsi_code = 6;
const uint8_t rdi_code = 7;
const uint8_t r8_code = 8;
const uint8_t r9_code = 9;
const uint8_t r10_code = 0Xa; //10
const uint8_t r11_code = 0xb; //11
const uint8_t r12_code = 0xc; //12
const uint8_t r13_code = 0xd; //13
const uint8_t r14_code = 0xe; //14
const uint8_t reg_invalid_code = 0xf; // 15 寄存器无效标记

// 条件码编码
const uint8_t ZF = 0;
const uint8_t SF = 1;
const uint8_t OF = 2;

// 程序状态编码
const uint8_t AOK = 1; //正常执行
const uint8_t HLT = 2; //执行停止指令halt
const uint8_t ADR = 3; //内存地址非法
const uint8_t INS = 4; //指令非法

// 指令操作码编码
const uint8_t halt_code = 0;
const uint8_t nop_code = 1;
const uint8_t rrmovq_code = 2; 
const uint8_t cmov_code = 2; //条件mov 同rrmoveq
const uint8_t irmovq_code = 3;
const uint8_t rmmovq_code = 4;
const uint8_t mrmovq_code = 5;
const uint8_t opq_code = 6; //算术或逻辑运算
const uint8_t jxx_code = 7; //跳转
const uint8_t call_code = 8;
const uint8_t ret_code = 9; 
const uint8_t pushq_code = 0xa; //10
const uint8_t popq_code = 0xb; //11
const uint8_t iopq_code = 0xc; //12 立即数算术或逻辑运算 ---> 也是指令编号最大值


// 算数运算符 ---> 6
const uint8_t add_code = 0;
const uint8_t sub_code = 1;
const uint8_t and_code = 2;
const uint8_t xor_code = 3;
  //算数运算符扩展
const uint8_t or_code = 4;
const uint8_t shl_code = 5; //逻辑左移
const uint8_t shr_code = 6; //逻辑右移
const uint8_t sar_code = 7; //算术右移
const uint8_t mulq_code = 8; //乘法
const uint8_t divq_code = 9; //除法
const uint8_t remq_code = 0xa; //取余


//条件判断（跳转jmp）(条件传送cmov) ---> 7 & 2
const uint8_t nonc_code = 0; //无条件码
const uint8_t le_code = 1;
const uint8_t l_code = 2;
const uint8_t e_code = 3;
const uint8_t ne_code = 4;
const uint8_t ge_code = 5;
const uint8_t g_code = 6;


//条件码结构体
struct condition_code{
    bool cc_valid = false;
    bool ZF = true;
    bool SF = false;
    bool OF = false;
};

//状态码结构体
struct stat_code{
    uint8_t new_stat = AOK;
    bool instr_valid = false;
    bool imem_error = false;
    bool dmem_error = false;
};

//CPU类
class CPU
{
private:
//CPU固有 ---> 当前状态
    uint8_t Stat = AOK;
    uint64_t PC = 0;
    uint64_t Reg[16] = {0};
    uint8_t Memory[MAXSIZE] = {0}; //8kb
    condition_code CC;

//各阶段需要用的变量 ---> 传递过程
    //取指
    uint8_t icode = nop_code;
    uint8_t ifun = 0;
    uint8_t rA = reg_invalid_code;
    uint8_t rB = reg_invalid_code;
    uint64_t valC = 0;
    uint64_t valP = 0;
    //译码
    uint64_t valA = 0;
    uint64_t valB = 0;
    uint8_t srcA = reg_invalid_code;
    uint8_t srcB = reg_invalid_code;
    //执行
    uint64_t ALU_A = 0;
    uint64_t ALU_B = 0; 
    uint8_t ALU_function = 0;
    uint64_t valE = 0;
    bool cnd = false;
    //访存
    uint64_t valM = 0;
    uint64_t address = 0;
    uint64_t data = 0;
    //写回
    uint8_t dstE = reg_invalid_code;
    uint8_t dstM = reg_invalid_code;
    //更新PC
    uint64_t refresh_PC = 0;
    //状态传递
    stat_code SC;
    //输出寄存器名称
    string reg_name[15] = {"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14"};

public: //按6个阶段定义所需函数
    //fetch
    void fetch();
    uint8_t r_icode(uint8_t first_bytes);
    uint8_t r_ifun(uint8_t first_bytes);
    uint8_t r_rA(uint8_t second_bytes);
    uint8_t r_rB(uint8_t second_bytes);
    uint64_t r_value(uint64_t other_bytes);
    bool InsValid();

    //decode
    void decode();
    void w_srcA();
    void w_srcB();
    void w_dstE();
    void w_dstM();

    //excute
    void execute();
    void r_ALU_A();
    void r_ALU_B();
    void ALU_calc(uint64_t A, uint64_t B, uint8_t function);
    bool condition();

    //memory
    void memory();
    void r_address();
    void r_data();
    void w_stat();
    void read(uint64_t addr);
    void write(uint64_t addr, uint64_t data);

    //writeback
    void writeback();

    //update_PC
    void update_PC();
    void w_PC();

    //others
    void reset();
    void run();
    bool judge_in(vector<uint8_t> check_list);

    //cin
    void input();
    

    //cout
    void print();
    

};

#endif // CPU_H