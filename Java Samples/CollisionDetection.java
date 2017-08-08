//Collision detection class containing methods for 2-dimensional collision detection of shapes
//Box-Box Box-Circle Circle-Circle

//Custom
import com.oregonmade.softbodies.screens.TestingGrounds.Box;
//Framework
import com.badlogic.gdx.utils.Array;

public class CollisionDetection
{
	Array<Shape>activeShapes;
	Array<Shape>inactiveShapes;
	private byte aType, bType;
	public CollisionDetection()
	{
		activeShapes = new Array();
	}
/*
	public void addShape(Array<Point> boundingVertices)
	{
		activeShapes.add(Shape(boundingVertices));
	}
*///Overload general polygon case later.
	public void addShape(Box box)
	{
		activeShapes.add(Shape(box,Shape.BOX));
	}
	public void checkForCollisions()
	{
		for(int j = 0; j < activeShapes.size; j++)
		{
			for(int i = 0; i < activeShapes.size; i++)
			{
				if(j!= i)
				{
					isColliding(activeShapes.get(j),activeShapes.get(i));
				}
			}
		}
	}
	public boolean isColliding(Shape a, Shape b)
	{
		//Determine type of shape a
		aType = a.getType();
		//Determine type of shape b
		bType = b.getType();
		//Run collision check algorithm of appropriate type
/*
		switch(aType):
			case Shape.RECTANGLE:
				if(bType == RECTANGLE)
				{
//					return(collisionTest(RECTANGLE,RECTANGLE)
				}
			break;
			case Shape.CIRCLE:
			break;
			case Shape.BOX:
			break;
			default:
			break;
		aType = null;
		bType = null;
		return(false);
*/
		if(aType == Shape.RECTANGLE && bType == Shape.RECTANGLE)
		{
			return(collisionTestRectangleRectangle(a,b));
		}
		return(false);
	}
	private boolean collisionTestRectangleRectangle(Shape a, Shape b)
	{
		Array<float> aVertices = a.getVertices();
		Array<float> bVertices = b.getVertices();
		//unrolling shape a points
		aAX = a.get(0);
		aAY = a.get(1);
		aBX = a.get(2);
		aBY = a.get(3);
		aCX = a.get(4);
		aCY = a.get(5);
		aDX = a.get(6);
		aDY = a.get(7);
		//unrolling shape b points
		bAX = b.get(0);
		bAY = b.get(1);
		bBX = b.get(2);
		bBY = b.get(3);
		bCX = b.get(4);
		bCY = b.get(5);
		bDX = b.get(6);
		bDY = b.get(7);
		if(aDX < bDX + b.getWidth() && aDX+a.getWidth() > bDX && aDY < bDY + b.getHeight()&& a.getHeight() + aDY > bDY)
		{
			System.out.println("Two Rectangles are colliding!");
			return(true)
		}
		return(false)
	}
	private class Shape()
	{
		public static final byte RECTANGLE = 0;
		public static final byte CIRCLE = 1;
		public static final byte SQUARE = 2;
		public static final byte TRIANGLE = 3;
		private byte Type = null;
		private Object liveReference = null;
		private Array<float> vertices = null;
		public Shape()
		{
			this.vertices = new Array();
		}
		public Shape(Box box, byte Type)
		{
			this.Type = Type;
			this.liveReference = box;
			this.vertices = new Array();
		}
		public byte getType()
		{
			return this.Type;
		}
		public void setReference(Object newReference)
		{
			this.liveReference = newReference;
		}
		public Object getReference()
		{
			return this.liveReference;
		}
		public void setType(byte newType)
		{
			this.Type = newType;
		}
		public Array<float> getVertices()
		{
			this.vertices.clear();
			if (this.Type == RECTANGLE)
			{
				Box boxReference = (Box)this.liveReference;
				this.vertices.add(boxReference.a.currentX);
				this.vertices.add(boxReference.a.currentY);
				this.vertices.add(boxReference.b.currentX);
				this.vertices.add(boxReference.b.currentY);
				this.vertices.add(boxReference.c.currentX);
				this.vertices.add(boxReference.c.currentY);
				this.vertices.add(boxReference.d.currentX);
				this.vertices.add(boxReference.d.currentY);
			}
			return(this.vertices);
		}
		public float getWidth()
		{
			Array<float> vertices = getVertices();
			float result;
			if(this.Type == RECTANGLE)
			{
				result = vertices.get(0) - vertices.get(2);
				if(result < 0)
				{
					result*=-1;
				}
				return(result);
			}
			return (-1.0f);
		}
		public float getHeight()
		{
			Array<float> vertices = getVertices();
			float result;
			if(this.Type == RECTANGLE)
			{
				result = vertice.get(1) - vertices.get(5);
				if(result < 0)
				{
					result*=-1;
				}
				return(result);
			}
			return(-1.0f);//default erroneous case
		}
	}
}
