package com.freeoakgames.rocketdodger;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by Griffter on 6/21/2017.
 */

public class RocketDodgerObjectAsyncManager
{/*
    static final RocketDodgerObjectAsyncManager sRocketDodgerObjectAsyncManager;
    private static  ThreadPoolExecutor mRocketDodgerThreadPoolExecutor;
    private static  BlockingQueue<Runnable> mRocketDodgerThreadPoolQueue;
    //private static final int CORE_POOL_SIZE = Runtime.getRuntime().availableProcessors();
    private static final int CORE_POOL_SIZE = 12;
    //running blocking queue schema it will only parallelize the tasks and never increase throughput beyond normal*cpu'sAvailable
    private static final int MAX_POOL_SIZE = CORE_POOL_SIZE;
    private static final long EXCESS_THREAD_LIFE_TIME = 5;//seconds to keep extra threads around
    private static final TimeUnit LIFE_TIME_UNIT = TimeUnit.SECONDS;
    static
    {
        sRocketDodgerObjectAsyncManager = new RocketDodgerObjectAsyncManager();
    }
    private RocketDodgerObjectAsyncManager()
    {
       mRocketDodgerThreadPoolQueue = new LinkedBlockingQueue<Runnable>();
        mRocketDodgerThreadPoolExecutor = new ThreadPoolExecutor(
                CORE_POOL_SIZE,
                MAX_POOL_SIZE,
                EXCESS_THREAD_LIFE_TIME,
                LIFE_TIME_UNIT,
                mRocketDodgerThreadPoolQueue
        );
    }
    public void tickObject(RocketDodgerObject rocketDodgerObject)
    {
        //if(!mRocketDodgerThreadPoolQueue.contains(rocketDodgerObject))
            sRocketDodgerObjectAsyncManager.mRocketDodgerThreadPoolExecutor.execute(rocketDodgerObject);
    }
    public static RocketDodgerObjectAsyncManager getInstance()
    {
        return sRocketDodgerObjectAsyncManager;
    }
    public static void waitForTasks()
    {
        while(!mRocketDodgerThreadPoolQueue.isEmpty())
        {
            //We are going to block until everything is done in the current queue;
        }
    }
    */
}
