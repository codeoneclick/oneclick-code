package common.mvc 
{
	import common.content.ContentEvent;
	import common.content.ContentLoader;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.net.URLRequest;
	import Game.Core;
	/**
	 * ...
	 * @author ...
	 */
	public class IViewer extends Sprite
	{
		private var m_url:String = "";
		private var m_dataType:String = "";
		
		public function IViewer(_url:String, _dataType:String) 
		{
			m_url = _url;
			m_dataType = _dataType;
			init();
		}
		
		private function init():void
		{
			if (m_dataType == ContentLoader.k_SWF_DATA)
			{
				addEventListener(ContentEvent.k_LOAD_SWF_DATA, onLoadCompleted);
			}
			else if (m_dataType == ContentLoader.k_BITMAP_DATA)
			{
				addEventListener(ContentEvent.k_LOAD_BITMAP_DATA, onLoadCompleted);
			}
			
			Core.contentLoader.request(m_url, this);	
		}
		
		private function onLoadCompleted(_event:IEvent):void
		{
			if (m_dataType == ContentLoader.k_SWF_DATA)
			{
				addChild(new _event.data.content);
			}
			else if (m_dataType == ContentLoader.k_BITMAP_DATA)
			{
				var bitmapData:BitmapData = _event.data.content;
				addChild(new Bitmap(bitmapData));
			}
			
			addEventListener(Event.ENTER_FRAME, update);
		}
		
		protected function update(_event:Event):void
		{
			
		}
	}

}