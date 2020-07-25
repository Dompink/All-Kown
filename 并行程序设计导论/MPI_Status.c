#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING= 100;
int main()
{
     char  greeting[MAX_STRING];
     int comm_sz;
     int my_rank;
     int q;
     int buffer_size=0;
     MPI_Status status;

     MPI_Init(NULL,NULL);
     MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
     MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

     if(my_rank != 0)
     {
        sprintf(greeting,"Greetings from process %d of %d!",my_rank,comm_sz);
        MPI_Send(greeting,strlen(greeting)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
     }
     else
     {
        printf("Greetings from process %d of %d !\n",my_rank,comm_sz);

        for(q=1;q<comm_sz;q++)
        {
            //对消息进行锁定测试（不接收消息） 
            /*
            int MPI_Probe(
                                #源进程序号 
                                int source, 
                                #消息标识
                                int tag, 
                                #通信子
                                MPI_Comm comm, 
                                #状态（返回的）
                                MPI_Status *status) 
            
            */
            MPI_Probe(q,0,MPI_COMM_WORLD,&status);
            MPI_Get_count(&status, MPI_CHAR, &buffer_size);
            MPI_Recv(greeting,buffer_size,MPI_CHAR,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("%s\n",greeting);
        }
     }
     MPI_Finalize();
    return 0;
}