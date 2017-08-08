package com.freeoakgames.rocketdodger;

import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.Vector3;

/**
 * Created by Griffter on 6/19/2017.
 */

public class RocketDodgerJetInputProcessor implements InputProcessor
{
    RocketDodgerJet mRocketDodgerJet;
    OrthographicCamera mOrthographicCamera;
    public RocketDodgerJetInputProcessor(RocketDodgerJet mRocketDodgerJet, OrthographicCamera mOrthographicCamera)
    {
        this.mRocketDodgerJet = mRocketDodgerJet;
        this.mOrthographicCamera = mOrthographicCamera;
        mRocketDodgerJet.attachControls(this);
    }
    @Override
    public boolean touchDragged(int x, int y, int pointer)
    {
        if(mRocketDodgerJet != null) {
            Vector3 worldCoordinates = mOrthographicCamera.unproject(new Vector3(x, y, 0));
            mRocketDodgerJet.setTargetAngle(RocketDodgerObject.getAngleTowardsPoint(new RocketDodgerLocation(worldCoordinates.x, worldCoordinates.y), mRocketDodgerJet.location));
        }
        return false;
    }

    @Override
    public boolean touchUp(int x, int y, int pointer, int button)
    {
        return false;
    }

    @Override
    public boolean touchDown(int x, int y, int pointer, int button)
    {
        if(mRocketDodgerJet != null) {
            Vector3 worldCoordinates = mOrthographicCamera.unproject(new Vector3(x, y, 0));
            mRocketDodgerJet.setTargetAngle(RocketDodgerObject.getAngleTowardsPoint(new RocketDodgerLocation(worldCoordinates.x, worldCoordinates.y), mRocketDodgerJet.location));
        }
        return false;
    }

    @Override
    public boolean keyTyped(char character)
    {
        return false;
    }

    @Override
    public boolean scrolled(int amount)
    {
        return false;
    }

    @Override
    public boolean keyDown(int keyCode)
    {
        return false;
    }

    @Override
    public boolean mouseMoved(int x, int y)
    {
        return false;
    }

    @Override
    public boolean keyUp(int keycode)
    {
        return false;
    }
}
