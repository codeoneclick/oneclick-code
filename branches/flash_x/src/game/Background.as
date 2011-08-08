package game 
{
	import core.Global;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.events.Event;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Background  extends Sprite
	{
		
		protected var m_container:DisplayObjectContainer = null;
		protected var m_bitmap:Bitmap = null;
		
		public function Background(_container:DisplayObjectContainer)  
		{
			m_container = _container;
			m_bitmap = new Bitmap();
			this.addChild(m_bitmap);
			m_container.addChild(this);
		}
		
		public function load(_name:String):void
		{
			Global.resourceController.loadPNG(_name, onLoadResource);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			m_bitmap.bitmapData = _data;
			Global.stage.addEventListener(Event.RESIZE, onResize);			
			Global.stage.dispatchEvent(new Event(Event.RESIZE));			
		}
		
		private function onResize(event:Event):void
		{
			graphics.beginBitmapFill(m_bitmap.bitmapData);
			graphics.drawRect(0, 0, Global.stage.stageWidth, Global.stage.stageHeight);
			graphics.endFill();
		}
	}
}