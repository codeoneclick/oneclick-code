package core 
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Camera 
	{
		private var m_position:Point = new Point(0, 0);
		
		public function Camera() 
		{
			
		}
		
		public function set position(_value:Point):void
		{
			m_position = _value;
		}
		
		public function get position():Point
		{
			return m_position;
		}
	
	}

}