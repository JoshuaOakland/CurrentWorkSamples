package com.freeoakgames.rocketdodger;

/**
 * Created by Griffter on 6/17/2017.
 */

public interface ActivityCommunicationsAdapter
{
    public void setScore(float newScore);
    public void onGameOver();
    public void onUpdate(RocketDodgerGameState rocketDodgerGameState);
}
