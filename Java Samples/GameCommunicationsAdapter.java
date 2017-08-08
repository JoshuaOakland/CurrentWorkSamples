package com.freeoakgames.rocketdodger;

/**
 * Created by Griffter on 6/19/2017.
 */

public interface GameCommunicationsAdapter
{
    public static final byte HUD_COMMAND_AFTERBURNER = 0;
    public static final byte HUD_COMMAND_QUICKTURN = 1;
    public static final byte HUD_COMMAND_FLARES = 2;
    public void onHudClicked(byte hudFlag);
}
