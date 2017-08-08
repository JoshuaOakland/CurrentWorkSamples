package com.freeoakgames.rocketdodger;


import com.badlogic.gdx.math.Vector2;

/**
 * Created by Griffter on 6/22/2017.
 */

public class RocketDodgerGeometry extends RocketDodgerObject
{
    public RocketDodgerGeometry(RocketDodgerTexturePalette gamePalette)
    {
        super(gamePalette);
        visibleSprite = gamePalette.getSprite(RocketDodgerGeometry.class);
        collider = generateCollisionPolygon(visibleSprite);
    }
    public RocketDodgerGeometry setLocationAndBounds(RocketDodgerLocation location, Vector2 dimensions)
    {
        this.location.setLocation(location.getX(),location.getY());
        this.visibleSprite.setBounds(location.getX(),location.getY(),dimensions.x,dimensions.y);
        this.collider = generateCollisionPolygon(this.visibleSprite);
        return this;
    }

}
