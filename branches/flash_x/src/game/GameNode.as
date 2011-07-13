package game 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.events.Event;
	import core.Global;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class GameNode extends Sprite
	{
		protected var m_container:DisplayObjectContainer = null;
		protected var m_intersect:Boolean = false;
		protected var m_bitmap:Bitmap = null;
	
		public function GameNode(_container:DisplayObjectContainer) 
		{
			m_container = _container;
			m_bitmap = new Bitmap();
		}
		
		public function Load(_name:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadResource);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			m_bitmap.bitmapData = _data;
			this.addChild(m_bitmap);
			m_container.addChild(this);
			
			addEventListener(Event.ENTER_FRAME, onUpdate, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOut, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOver, false, 0, true);
		}
		
		protected function onUpdate(_event:Event):void
		{
			if (m_intersect)
			{
				filters = [new GlowFilter(0x00FFFFFF)];
			}
			else
			{
				filters = null;
			}
			
			x -= Global.camera.offset.x;
			y -= Global.camera.offset.y;
		}
		
		protected function onMouseOut(_event:MouseEvent):void
		{
			m_intersect = false;
		}
		
		protected function onMouseOver(_event:MouseEvent):void
		{
			m_intersect = true;
		}
		
	}

}