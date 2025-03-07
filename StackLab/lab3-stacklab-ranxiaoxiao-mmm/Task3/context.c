#include "context.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"

__generator __main_gen;
__generator* __now_gen = &__main_gen;

// Task 2

void __err_stk_push(__ctx* ctx){
    assert(ctx != 0);
    __err_stk_node* new = (__err_stk_node*)malloc(sizeof(__err_stk_node));
    new->ctx = ctx;
    new->prev = __now_gen->__err_stk_head;
    __now_gen->__err_stk_head = new;

    // TODO
}

__ctx* __err_stk_pop(){
    assert(__now_gen->__err_stk_head != 0);
    __err_stk_node* top = __now_gen->__err_stk_head;
    __now_gen->__err_stk_head = top->prev;
    __ctx* popctx = top->ctx;
    free(top);
    return(popctx);

    // TODO
}

void __err_cleanup(const int* error){
    if(*error == 0){
        __ctx* popctx;
        popctx = __err_stk_pop();
    }
    // TODO
}

int __check_err_stk(){
    return __now_gen->__err_stk_head == 0;
}

// Task 3

int send(__generator* gen, int value) {
    if (gen == 0) throw(ERR_GENNIL);
    gen->data = value;
    gen->caller = __now_gen;
    if(__ctx_save(&(__now_gen->ctx)) == 0){
        __now_gen = gen;
        __ctx_restore(&(gen->ctx),1);
    }
    // TODO

    return gen->data;
}

int yield(int value) {
    if (__now_gen->caller == 0) throw(ERR_GENNIL);
    __now_gen->data = value;
    __generator* call_gen = __now_gen->caller;
     call_gen->data = value;
    if(__ctx_save(&(__now_gen->ctx)) == 0){
        __now_gen = call_gen;
        __ctx_restore(&(call_gen->ctx),1);
    }
    // TODO

    return __now_gen->data;
}

__generator* generator(void (*f)(int), int arg) {
    __generator* gen = (__generator*)malloc(sizeof(__generator));
    memset(gen,0,sizeof(__generator));
    gen->f = f;
    gen->stack = malloc(10000); 
    gen->caller = __now_gen;
    gen->__err_stk_head = NULL;

    //计算栈起始空间
    char* stack_top = (char*)gen->stack + 10000;
    while((unsigned long)stack_top % 16 != 0){
        stack_top--;
    }
    long long* handctx = (long long*)gen->ctx;
    *handctx = (long long)gen_tram;
    *(handctx+2) = (long long)stack_top;
    *(handctx+1) = (long long)stack_top;
    *(handctx+10) = (long long)arg;
    return gen;
    // TODO: construct a new generator
}

void generator_free(__generator** gen) {
    if (*gen == NULL) throw(ERR_GENNIL);
    free((*gen)->stack);
    while ((*gen)->__err_stk_head != 0) {
        __err_stk_node* tmp = (*gen)->__err_stk_head;
        (*gen)->__err_stk_head = (*gen)->__err_stk_head->prev;
        free(tmp->ctx);
        free(tmp);
    }
    free(*gen);
    *gen = NULL;
}

void gen_tram(int arg){
    __generator* gen = __now_gen;
    gen->f(arg);
    throw(ERR_GENEND);
    assert(0); 
}

void gen_throw(int x){
    throw(x);
    assert(0);
}