package Game.elements 
{
	import common.mvc.IModel;
	import common.mvc.IViewer;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class TileModel extends IModel
	{
		private var m_screenPosition:Point = new Point(0, 0);
		
		public function TileModel() 
		{
			super();
		}
		
		public function get screenPosition():Point
		{
			return m_screenPosition;
		}
		
		public function setScreenPosition(_x:int, _y:int):void
		{
			m_screenPosition = new Point(_x, _y);
			super.dispatchEvent(new TileEvent(TileEvent.k_UPDATE_POSITION,m_screenPosition));
		}
		
		public function onMouseOver(_event:MouseEvent):void
		{
			super.dispatchEvent(new TileEvent(TileEvent.k_MOUSE_OVER, null));
		}
		
		public function onMouseOut(_event:MouseEvent):void
		{
			super.dispatchEvent(new TileEvent(TileEvent.k_MOUSE_OUT, null));
		}
		
	}

}