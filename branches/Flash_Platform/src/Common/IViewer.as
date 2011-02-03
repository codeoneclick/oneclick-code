package Common 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.net.URLRequest;
	/**
	 * ...
	 * @author ...
	 */
	public class IViewer extends Sprite
	{
		private static const k_SWF:String = "application/x-shockwave-flash";
		private static const k_JPEG:String = "image/jpeg";
		private static const k_GIF:String = "image/gif";
		private static const k_PNG:String = "image/png";
		
		public static const k_SWF_DATA:String = "swf_data";
		public static const k_BITMAP_DATA:String = "bitmap_data";
		
		private var m_url:String = "";
		private var m_loader:Loader = null;
		private var m_isLoad:Boolean = false;
		private var m_dataType:String = "";
		
		public function IViewer(_url:String, _dataType:String) 
		{
			m_url = _url;
			m_isLoad = false;
			m_dataType = _dataType;
			init();
		}
		
		private function init():void
		{
			m_loader = new Loader();
			m_loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onLoad);
			m_loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, onLoadIOError);
			m_loader.load(new URLRequest(m_url));
			if (m_dataType == k_SWF_DATA)
			{
				addEventListener(IEvent.k_LOAD_SWF_DATA, onLoadCompleted);
			}
			else if (m_dataType == k_BITMAP_DATA)
			{
				addEventListener(IEvent.k_LOAD_BITMAP_DATA, onLoadCompleted);
			}
		}
		
		private function onLoadCompleted(_event:IEvent):void
		{
			if (m_dataType == k_SWF_DATA)
			{
				addChild(new _event.data.content);
			}
			else if (m_dataType == k_BITMAP_DATA)
			{
				var bitmapData:BitmapData = _event.data.content;
				addChild(new Bitmap(bitmapData));
			}
			
			addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function onLoad(_event:Event):void
		{
			var data:Object = new Object();
			data.url = m_url;
			switch(_event.target.contentType)
			{
				case k_SWF:
					data.content = _event.target.applicationDomain.getDefinition("") as Class;
					dispatchEvent(new IEvent(IEvent.k_LOAD_SWF_DATA, data));
					break;
				case k_PNG:
					data.content = _event.target.content.bitmapData;
					dispatchEvent(new IEvent(IEvent.k_LOAD_BITMAP_DATA, data));
					break;
				default:
					throw new Error("unknown content");
			}
        }
		
		private function onLoadIOError(_event:IOErrorEvent):void
		{
			throw new Error("content no found");
		}
		
		protected function update(_event:Event):void
		{
			
		}
	}

}