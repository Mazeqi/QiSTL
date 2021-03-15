/*  file Main.cpp
*
*  This program is an adaptation of the code Rex Jaeschke showed in
*  Listing 1 of his Oct 2005 C/C++ User's Journal article entitled
*  "C++/CLI Threading: Part I".  I changed it from C++/CLI (managed)
*  code to standard C++.
*
*  One hassle is the fact that C++ must employ a free (C) function
*  or a static class member function as the thread entry function.
*
*  This program must be compiled with a multi-threaded C run-time
*  (/MT for LIBCMT.LIB in a release build or /MTd for LIBCMTD.LIB
*  in a debug build).
*
*                                      John Kopplin  7/2006
*/


#include  < stdio.h >
#include  < string >               //  for STL string class
#include  < windows.h >            //  for HANDLE
#include  < process.h >            //  for _beginthread()
#include  <iostream>
using   namespace  std;

// In C++ you must employ a free (C) function or a static
// class member function as the thread entry-point-function.
// Furthermore, _beginthreadex() demands that the thread
// entry function signature take a single (void*) and returned
// an unsigned.


class  ThreadX
{
public:
    int loop_value;

public:
    string threadName;

    ThreadX(int endValue)
    {
        loop_value = endValue;
    }

   
    void ThreadEntryPoint(int test_num)
    {
       // for(int i = 0; i < 100; i++)
        cout << test_num << std::endl;
    }
};

 unsigned int __stdcall ThreadStaticEntryPoint(void* pThis)
{
    ThreadX* pthX = (ThreadX*)pThis;   // the tricky cast
    int value = pthX->loop_value;
    //pthX->loop_value = -1;
    //cout << value;
    pthX->ThreadEntryPoint(value);          

    return 0;          
}


int  main()
{
    

    ThreadX* o1 = new ThreadX(2000);

    const int thread_num = 5;
    HANDLE handle[thread_num];
    for (int i = 0; i < 10; ++i) {
        o1->loop_value = i;
        handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadStaticEntryPoint, o1, 0, NULL);
        ResumeThread(handle[i]);
    }

    //HANDLE handle = CreateThread(NULL,0,ThreadFun,NULL,0,NULL);

    //WaitForSingleObject(handle,INFINITE);
    WaitForMultipleObjects(thread_num, handle, true, INFINITE); //为了防止子线程没有执行就结束了.
    return 0;

   
    //HANDLE   hth1;
    //unsigned  uiThread1ID;

    //hth1 = (HANDLE)_beginthreadex(NULL,         // security
    //    0,            // stack size
    //    ThreadStaticEntryPoint,
    //    o1,           // arg list
    //    0,  // so we can later call ResumeThread()
    //    &uiThread1ID);

    //o1->loop_value = -1;

    //if (hth1 == 0)
    //    printf("Failed to create thread 1\n");

   
    //CloseHandle(hth1);
   
    //delete o1;
   // o1 = NULL;

   // printf(" Primary thread terminating.\n ");
}