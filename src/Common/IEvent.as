package Common 
{
	import flash.events.Event;
	/**
	 * ...
	 * @author ...
	 */
	public class IEvent extends Event
	{
		public static var k_LOAD_SWF_DATA:String = "load_swf_data";
		public static var k_LOAD_BITMAP_DATA:String = "load_bitmap_data";
		
		private var m_data:*;
		public function IEvent(_event:String,_data:*) 
		{
			m_data = _data;
			super(_event, false, false);
		}
		
		public function get data():*
		{
			return m_data;
		}
		
	}

}