package common.resource 
{
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class ResourceController 
	{	
		private static const k_PNG_EXT:String = ".png";
		
		private static var m_path:String = "content/";
		
		private var m_cacheResource:Dictionary = new Dictionary();
		private var m_callbackQueue:Dictionary = new Dictionary();
		
		public function ResourceController() 
		{
			
		}
		
		public static function set path(_value:String):void
		{
			m_path = _value;
		}
		
		public static function get path():String
		{
			return m_path;
		}
		
		public function loadPNG(_name:String, _callback:Function):void
		{
			if ( m_cacheResource[_name] != null)
			{
				_callback(m_cacheResource[_name]);
			}
			else if (m_callbackQueue[_name] != null)
			{
				(m_callbackQueue[_name] as ResourceRequest).callbackList.push(_callback);
			}
			else
			{
				var request:ResourceRequest = new ResourceRequest();
				request.callbackList.push(_callback);
				m_callbackQueue[_name] = request;
				
				request.loader = new Loader();
				request.loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onLoadComplete, false, 0, true);
				request.loader.load(new URLRequest(m_path + _name + k_PNG_EXT));
			}
		}
		
		private function onLoadComplete(_event:Event):void
		{
			var url:String = _event.target.url;
			var name:String = url.substring(m_path.length + url.search(m_path), url.length - k_PNG_EXT.length);
			m_cacheResource[name] = _event.target.content.bitmapData;
			
			if (m_callbackQueue[name] != null)
			{
				for (var i:int = 0; i < (m_callbackQueue[name] as ResourceRequest).callbackList.length; i++)
				{
					((m_callbackQueue[name] as ResourceRequest).callbackList[i] as Function)(_event.target.content.bitmapData);
				}
				(m_callbackQueue[name] as ResourceRequest).callbackList = new Vector.<Function>();	
			}
		}
		
	}

}