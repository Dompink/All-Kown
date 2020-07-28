#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);
int main(int argc,char* argv[])
{       
         /*
             long strtol( 
                        const char* number_p *in*, 第一个参数是字符串
                        const char** end_p  *out*,终止的非法字符串 
                        int     base  *in* 进制（2-36）
                        ）
            
            例：
            char buffer[20]="10379cend$3";
            char *stop;
            printf("%d\n",strtol(buffer, &stop, 2));
            printf("%s\n", stop);
            输出结果：
            2
            379cend$3
        */
        int thread_count = strtol(argv[1],NULL,10);
#pragma omp parallel num_threads(thread_count)
        Hello();
        
        return 0;
}

void Hello(void)
{
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    printf("hello from thread %d of %d \n",my_rank,thread_count);
}
