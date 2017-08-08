package com.freeoakgames.rocketdodger;

import java.util.ArrayList;

/**
 * Created by Griffter on 6/20/2017.
 */

public class RocketDodgerObjectManager
{
    ArrayList<RocketDodgerObject> mRocketDodgerObjectCleaningList;
    boolean bIsNeedingCleanup;
    public RocketDodgerObjectManager()
    {
        mRocketDodgerObjectCleaningList = new ArrayList<RocketDodgerObject>();
    }
    public void manageLifecycle(ArrayList<RocketDodgerObject> rocketDodgerObjectArrayList)
    {
        for(RocketDodgerObject rocketDodgerObject : rocketDodgerObjectArrayList)
        {
            if(RocketDodger.isMissile(rocketDodgerObject))
            {
                handleMissile((RocketDodgerMissile)rocketDodgerObject);
            }
            else if(RocketDodger.isFlare(rocketDodgerObject))
            {
                handleFlare((RocketDodgerFlare)rocketDodgerObject);
            }
            else if (RocketDodger.isJet(rocketDodgerObject))
            {
                handleJet((RocketDodgerJet)rocketDodgerObject);
            }
            else if (RocketDodger.isSpecialEffect(rocketDodgerObject))
            {
                handleSpecialEffect((RocketDodgerSpecialEffect)rocketDodgerObject);
            }
        }
    }

    public void handleSpecialEffect(RocketDodgerSpecialEffect effect)
    {
        if(effect.effectDuration <= 0)
        {
            effect.dispose();
            mRocketDodgerObjectCleaningList.add(effect);
        }
    }

    public void handleJet(RocketDodgerJet jet)
    {
        if(jet.isDead)
        {
            mRocketDodgerObjectCleaningList.add(jet);
        }
    }
    public void handleFlare(RocketDodgerFlare flare)
    {
        if(flare.lifeTime >= flare.BURNOUT_TIME)
        {
            mRocketDodgerObjectCleaningList.add(flare);
        }
    }
    public void handleMissile(RocketDodgerMissile missile)
    {
        if((missile.bIsOutOfFuel && (missile.location.getY() < 0)) || (missile.location.getY() < 0))
        {
            mRocketDodgerObjectCleaningList.add(missile);
        }
    }

    public void performCleanup(ArrayList<RocketDodgerObject> rocketDodgerObjectArrayList)
    {
        for(RocketDodgerObject rocketDodgerObject : mRocketDodgerObjectCleaningList)
        {
            if(rocketDodgerObjectArrayList.contains(rocketDodgerObject))
            {
                rocketDodgerObjectArrayList.remove(rocketDodgerObject);
            }
        }
        mRocketDodgerObjectCleaningList.clear();
        //now that it is all said and done launch a cleaning thread to take out trash
    }
}

