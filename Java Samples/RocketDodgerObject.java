package com.freeoakgames.rocketdodger;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Polygon;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;

/**
 * Created by Griffter on 6/17/2017.
 */

public class RocketDodgerObject implements Runnable
{
    @Override
    public void run()
    {
        tick(RocketDodgerGameState.currentDeltaTime);
//        tick(Gdx.graphics.getDeltaTime());
    }
    protected Polygon collider;
    protected Sprite visibleSprite;
    protected RocketDodgerLocation location;
    protected RocketDodgerRotation rotation;
    public void tick(float deltaTime)
    {
        //if moving increment location
        //handle animations
        //update state machines
    }
    protected static void rationalizeSprite(Sprite irrationalSprite, int factor)
    {
        if(factor < 0)
        {
            factor = 1;
        }
        float ratio = irrationalSprite.getHeight()/irrationalSprite.getWidth();
        irrationalSprite.setBounds(0,0, Gdx.graphics.getWidth()/factor,(Gdx.graphics.getWidth()/factor)*ratio);
        irrationalSprite.setOrigin((irrationalSprite.getWidth()*irrationalSprite.getScaleX())/2,(irrationalSprite.getHeight()*irrationalSprite.getScaleY())/2);
    }
    public void draw(SpriteBatch batch)
    {
        this.visibleSprite.draw(batch);
    };
    public RocketDodgerObject(RocketDodgerTexturePalette gamePalette)
    {
        location = new RocketDodgerLocation();
        rotation = new RocketDodgerRotation();
        collider = new Polygon();
        visibleSprite = gamePalette.getSprite(RocketDodgerObject.class);
    }
    protected void maintainState()
    {
        this.visibleSprite.setPosition(this.location.getX(),this.location.getY());
        this.visibleSprite.setRotation(this.rotation.getRotation());
        this.collider.setPosition(this.location.getX(),this.location.getY());
        this.collider.setRotation(this.rotation.getRotation());
    }
    protected static Polygon generateCollisionPolygon(Sprite targetSprite)
    {
        Polygon newCollsionable = null;
        Rectangle spriteBounds = targetSprite.getBoundingRectangle();
        newCollsionable = new Polygon(new float[]{0.0f,0.0f, spriteBounds.width,0.0f,spriteBounds.width,spriteBounds.height,0.0f,spriteBounds.height});
        newCollsionable.setOrigin(.5f*spriteBounds.width,.5f*spriteBounds.height);
        return newCollsionable;
    }
    protected static void move(float movementSpeed, float rotationAngle, RocketDodgerLocation currentLocation)
    {
        //get dX from speed and angle
        float deltaX = movementSpeed * MathUtils.cos(MathUtils.degreesToRadians*rotationAngle);
        float deltaY = movementSpeed * MathUtils.sin(MathUtils.degreesToRadians*rotationAngle);
        currentLocation.incrementLocation(deltaX,deltaY);
        //get dY from speed and angle
        //increment currentLocation by deltas
    }
    //returns delta angle to apply to steering of an object
    public static float makeTurn(float turnRate, float speedOfObject, float massOfObject, float currentHeading, float desiredHeading)
    {
        float turnAmount = 0.0f;
        float resistance = MathUtils.clamp(speedOfObject*massOfObject,0.1f,2.0f);
        float deltaAngle = currentHeading - desiredHeading;
        if(resistance != 0)
            turnAmount = MathUtils.lerp(currentHeading, desiredHeading, turnRate/resistance);
        else
            turnAmount = MathUtils.lerp(currentHeading, desiredHeading, turnRate);
        //return MathUtils.clamp(turnAmount, -turnRate, turnRate);
        return turnAmount;
    }
    public static Vector2 makeVelocity(float movementSpeed, float rotationAngle, Vector2 updatedVelocity)
    {
        updatedVelocity.x = movementSpeed * MathUtils.cos(MathUtils.degreesToRadians*rotationAngle);
        updatedVelocity.y = movementSpeed * MathUtils.sin(MathUtils.degreesToRadians*rotationAngle);
        //updatedVelocity.x = movementSpeed * (float)Math.cos((MathUtils.degreesToRadians*rotationAngle));
        //updatedVelocity.y = movementSpeed * (float)Math.sin((MathUtils.degreesToRadians*rotationAngle));
        return updatedVelocity;
    }
    public static Vector2 makeVelocity(float movementSpeed, float rotationAngle)
    {
        Vector2 calculatedVelocity = new Vector2(0,0);
        calculatedVelocity.x = movementSpeed * MathUtils.cos(MathUtils.degreesToRadians*rotationAngle);
        calculatedVelocity.y = movementSpeed * MathUtils.sin(MathUtils.degreesToRadians*rotationAngle);
        //calculatedVelocity.x = movementSpeed * (float)Math.cos((MathUtils.degreesToRadians*rotationAngle));
        //calculatedVelocity.y = movementSpeed * (float)Math.sin((MathUtils.degreesToRadians*rotationAngle));
        return calculatedVelocity;
    }
    public static class RocketDodgerObjectClassTypes
    {
        final static byte TALOS = 0;
        final static byte JET = 1;
        final static byte HOMING = 2;
        final static byte FLARE = 3;
    }
    public static float getAngleTowardsPoint(RocketDodgerLocation destination, RocketDodgerLocation origin)
    {
        float targetAngle = MathUtils.radiansToDegrees * MathUtils.atan2(destination.getY() - origin.getY(),destination.getX() - origin.getX());
        return targetAngle;
    }
}
