package Common 
{
	import flash.events.Event;
	/**
	 * ...
	 * @author ...
	 */
	public class testViewer extends IViewer
	{
		
		public function testViewer() 
		{
			super("content/element_ground.png","bitmap_data");
		}
		
		override protected function update(event:Event):void
		{
			trace("ololol");
		}
		
	}

}