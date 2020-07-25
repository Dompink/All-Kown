#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define SIZE 6
int main(int argc,char* argv[])
{
        int my_rank;
        int comm_sz;
        int src=0;
        int dest=1;
        int i,bsize,tsize;
        int buffer[SIZE];
        char* tmpbuffer;
        int* tmpbuf;
        int* recv_b;

        MPI_Init(NULL,NULL);
        MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
        MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
        if(my_rank == src)
        {
            for(i=0;i<SIZE;i++)
                buffer[i]=i;

            MPI_Pack_size(SIZE,MPI_INT,MPI_COMM_WORLD,&bsize);
            tmpbuffer =(char*) malloc(bsize+MPI_BSEND_OVERHEAD);
            MPI_Buffer_attach(tmpbuffer,bsize+MPI_BSEND_OVERHEAD);

            for(dest=1;dest<comm_sz;dest++)
            {
                MPI_Bsend(buffer,SIZE,MPI_INT,dest,2000,MPI_COMM_WORLD);
                buffer[dest]=buffer[dest]*2;

            }
            MPI_Buffer_detach(&tmpbuf,&tsize);


        }
        else
        {
            /*
            if(my_rank==1)
            {
                int index=0;
                while(index<3e8)
                {
                        index++;
                }
            }*/
            recv_b=malloc(SIZE*sizeof(int));
            MPI_Recv(recv_b,SIZE,MPI_INT,src,2000,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //printf("%d ------        oook\n",my_rank);
            for(i=0;i<SIZE;i++)
                printf("%d -> %d\n",my_rank,recv_b[i]);
            printf("----------->\n");
        }
        MPI_Finalize();
        return 0;
}
