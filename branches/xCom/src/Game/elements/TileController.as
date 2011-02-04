package Game.elements 
{
	import common.mvc.IController;
	import flash.display.DisplayObjectContainer;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class TileController extends IController
	{
		private var m_dataPath:String = "content/element_ground.png";
		private var m_dataType:String = "bitmap_data";
		
		public function TileController(_container:DisplayObjectContainer) 
		{
			super(_container, new TileViewer(m_dataPath, m_dataType), new TileModel());
			init();
		}
		
		private function init():void
		{
			m_model.addEventListener(TileEvent.k_UPDATE_POSITION, onPositionUpdate);
			m_model.addEventListener(TileEvent.k_MOUSE_OVER, onMouseOver);
			m_model.addEventListener(TileEvent.k_MOUSE_OUT, onMouseOut);
			
			m_viewer.addEventListener(MouseEvent.MOUSE_OVER, (m_model as TileModel).onMouseOver);
			m_viewer.addEventListener(MouseEvent.MOUSE_OUT, (m_model as TileModel).onMouseOut);
		}
		
		private function onPositionUpdate(_event:TileEvent):void
		{
			var screenPosition:Point = _event.data;
			m_viewer.x = screenPosition.x;
			m_viewer.y = screenPosition.y;
		}
		
		public function setScreenPosition(_x:int, _y:int):void
		{
			(m_model as TileModel).setScreenPosition(_x, _y);
		}
		
		private function onMouseOver(_event:TileEvent):void
		{
			m_viewer.filters = [new GlowFilter()];
		}
		
		private function onMouseOut(_event:TileEvent):void
		{
			m_viewer.filters = null;
		}
	}

}