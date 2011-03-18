package game.enviroment 
{
	import flash.display.DisplayObjectContainer;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class GroundCell extends GameNode
	{
		public static const k_WIDTH:int = 64;
		public static const k_HEIGHT:int = 64;
		
		public function GroundCell(_container:DisplayObjectContainer, _size:Point, _resName:String) 
		{
			super(_container, _size, _resName);
		}
		
	}

}