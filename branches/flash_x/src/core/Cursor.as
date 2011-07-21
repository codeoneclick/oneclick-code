package core 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Cursor extends Sprite
	{
		protected var m_container:DisplayObjectContainer = null;
		protected var m_bitmap:Bitmap = null;
		
		public function Cursor(_container:DisplayObjectContainer) 
		{
			m_container = _container;
			m_container.addChild(this);
			m_bitmap = new Bitmap();
			addChild( m_bitmap );
			addEventListener(Event.ENTER_FRAME, onUpdate, false, 0, true);
			
			mouseEnabled = false;
		}
		
		public function Load(_name:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadResource);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			m_bitmap.bitmapData = _data;
		}
		
		protected function onUpdate(_event:Event):void
		{
			x = Global.input.mousePosition.x - this.width / 4;
			y = Global.input.mousePosition.y;
		}
		
	}

}