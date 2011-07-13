package common.resource 
{
	import flash.display.Loader;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class ResourceRequest 
	{
		
		private var m_loader:Loader = null;
		private var m_callbackList:Vector.<Function> = new Vector.<Function>();
		
		public function ResourceRequest() 
		{
			
		}
		
		public function set loader(_value:Loader):void
		{
			m_loader = _value;
		}
		
		public function get loader():Loader
		{
			return m_loader;
		}
		
		public function set callbackList(_value:Vector.<Function>):void
		{
			m_callbackList = _value;
		}
		
		public function get callbackList():Vector.<Function>
		{
			return m_callbackList;
		}
		
	}

}