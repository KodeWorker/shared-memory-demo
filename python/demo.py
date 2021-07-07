# https://blog.csdn.net/zcz_822/article/details/105858962
import mmap
import time
 
if __name__ == "__main__":

    content = "hello world!"
    byte = content.encode()
    SHMEMSIZE = len(content)
    #SHMEMSIZE = 1024
     
    file_name = "global_share_memory"
    print(file_name, SHMEMSIZE)
    
    # python write  shared memory
    shmem = mmap.mmap(-1, SHMEMSIZE, file_name, mmap.ACCESS_WRITE)
    shmem.write(byte)
    #shmem.close()
    
    while True:
        # python read shared memory
        shmem = mmap.mmap(-1, SHMEMSIZE, file_name, mmap.ACCESS_READ)
        #print(shmem.read(2))
        print(shmem.read(SHMEMSIZE).decode("utf-8"))
        #print(shmem.read(SHMEMSIZE).decode("ansi"))    
        time.sleep(1)    
    shmem.close()
    