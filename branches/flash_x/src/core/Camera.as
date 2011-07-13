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
		private var m_offset:Point = new Point(0, 0);
		
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
		
		public function set offset(_value:Point):void
		{
			m_offset = _value;
		}
		
		public function get offset():Point
		{
			return m_offset;
		}
	}

}