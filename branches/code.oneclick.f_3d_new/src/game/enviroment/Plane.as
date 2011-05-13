package game.enviroment 
{
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author ...
	 */
	public class Plane extends SimpleNode
	{
		public static const k_WIDTH:int = 64;
		public static const k_HEIGHT:int = 64;
		
		protected var m_index:Point = new Point(0, 0);
		
		public function Plane(_container:DisplayObjectContainer, _size:Point, _resName:String) 
		{
			super(_container, _size, _resName);
		}

		override protected function update():void 
		{
			super.update();
		}
	}
}