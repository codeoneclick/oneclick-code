package common.content 
{
	import common.mvc.IEvent;
	/**
	 * ...
	 * @author ...
	 */
	public class ContentEvent extends IEvent
	{
		public static var k_LOAD_SWF_DATA:String = "load_swf_data";
		public static var k_LOAD_BITMAP_DATA:String = "load_bitmap_data";
		
		public function ContentEvent(_event:String,_data:*) 
		{
			super(_event, _data);
		}
		
	}

}