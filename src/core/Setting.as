package core 
{
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Setting 
	{
		
		private var m_windowWidth:int  = 800;
		private var m_windowHeight:int = 600;
		
		public function Setting() 
		{
			
		}
		
		public function set windowWidth(_value:int):void
		{
			m_windowWidth = _value;
		}
		
		public function get windowWidth():int
		{
			return m_windowWidth;
		}
		
		public function set windowHeight(_value:int):void
		{
			m_windowHeight = _value;
		}
		
		public function get windowHeight():int
		{
			return m_windowHeight;
		}
		
	}

}