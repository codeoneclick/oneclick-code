package common.content 
{
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.net.URLRequest;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author ...
	 */
	public class ContentLoader
	{
		private static const k_SWF:String = "application/x-shockwave-flash";
		private static const k_JPEG:String = "image/jpeg";
		private static const k_GIF:String = "image/gif";
		private static const k_PNG:String = "image/png";
		private static const k_CONTENT_PATH:String = "content/";
		
		public static const k_SWF_DATA:String = "swf_data";
		public static const k_BITMAP_DATA:String = "bitmap_data";
		
		private var m_requesterList:Dictionary = null;
		private var m_resourceContainer:Dictionary = null;
		
		public function ContentLoader() 
		{
			init();
		}
		
		private function init():void
		{
			m_requesterList = new Dictionary();
			m_resourceContainer = new Dictionary();
		}
		
		public function request(_url:String,_requester:*):void
		{
			if (m_resourceContainer[_url] != null)
			{
				_requester.dispatchEvent(new ContentEvent(ContentEvent.k_LOAD_SWF_DATA, m_resourceContainer[_url]));
				return;
			}
			else if (m_requesterList[_url] != null)
			{
				m_requesterList[_url].requester.push(_requester);
				return;
			}
			
			var request:ContentRequest = new ContentRequest();
			m_requesterList[_url] = request;
			request.requester.push(_requester);
			request.loader = new Loader();
			request.loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onComplete);
			request.loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, onError);
			request.loader.load(new URLRequest(_url));
		}
		
		private function onComplete(_event:Event):void
		{
			var data:Object = new Object();
			var url:String = _event.target.url.substring(_event.target.url.search(k_CONTENT_PATH), _event.target.url.length);
			var index:int = 0;
			var requester:ContentRequest = null;
			
			switch(_event.target.contentType)
			{
				case k_SWF:
					data.content = _event.target.applicationDomain.getDefinition("") as Class;
					requester = m_requesterList[url];
					if (requester != null)
					{
						m_resourceContainer[_event.target.url] = data;
						for (index = 0; index < requester.requester.length; index++)
						{
							requester.requester[index].dispatchEvent(new ContentEvent(ContentEvent.k_LOAD_SWF_DATA, data));
						}
					}
					else
					{
						throw Error("No requester found");
					}
					
					break;
				case k_PNG:
					data.content = _event.target.content.bitmapData;
					requester = m_requesterList[url];
					if (requester != null)
					{
						m_resourceContainer[_event.target.url] = data;
						for (index = 0; index < requester.requester.length; index++)
						{
							requester.requester[index].dispatchEvent(new ContentEvent(ContentEvent.k_LOAD_BITMAP_DATA, data));
						}
					}
					else
					{
						throw Error("No requester found");
					}
					break;
				default:
					throw new Error("Unknown content");
			}
		}
		
		private function onError(_event:IOErrorEvent):void
		{
			throw Error("Content can't be loaded");
		}
		
	}
}