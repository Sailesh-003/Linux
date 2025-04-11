#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/delay.h>

#define NUM_THREADS 3

static struct task_struct *threads[NUM_THREADS];
static int count = 0;
static struct mutex lock;

static int thread_function(void *data)
{
        int thread_id = *(int *)data;

        pr_info("Thread %d created successfully\n",thread_id);

        for(int i=0; i<10000; i++)
        {
                mutex_lock(&lock);
                count++;
                mutex_unlock(&lock);
        }

        pr_info("Thread %d updated the count value to: %d\n",thread_id,count);
        pr_info("Thread %d id finished\n",thread_id);

        return 0;
}

static int __init kthread_mutex_init(void)
{
        pr_info("Module successfully Inserted\n");

        mutex_init(&lock);

        for(int i=0; i<NUM_THREADS; i++)
        {
                int id = i+1;
                threads[i] = kthread_create(thread_function,&id,"kthread %d",i);

                if(!IS_ERR(threads[i]))
                {
                        wake_up_process(threads[i]);
                        ssleep(1);
                }
        }

        return 0;
}

static void __exit kthread_mutex_exit(void)
{
        for(int i=0; i<NUM_THREADS; i++)
        {
                pr_info("Stopping thread %d\n",i);
                kthread_stop(threads[i]);
        }

        mutex_destroy(&lock);

        pr_info("Module successfully removed\n");
}

module_init(kthread_mutex_init);
module_exit(kthread_mutex_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sailesh");
MODULE_DESCRIPTION("Example Program of Kernel Thread with Mutex");
