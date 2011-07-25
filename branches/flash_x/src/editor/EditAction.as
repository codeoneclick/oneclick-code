package editor 
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class EditAction 
	{
		public static const k_ADD_ACTION:String = "ADD_ACTION";
		public static const k_CHANGE_ACTION:String = "CHANGE_ACTION";
		public static const k_REMOVE_ACTION:String = "REMOVE_ACTION";
		
		
		private var m_action:String = "";
		private var m_position:Point = new Point();
		private var m_sectorType:String = "";
		private var m_sectorName:String = "";
		private var m_oldSectorName:String = "";
		
		public function EditAction() 
		{
			
		}
		
		public function set action(_value:String):void
		{
			m_action = _value;
		}
		
		public function get action():String
		{
			return m_action;
		}
		
		public function set position(_value:Point):void
		{
			m_position = _value;
		}
		
		public function get position():Point
		{
			return m_position;
		}
		
		public function set sectorType(_value:String):void
		{
			m_sectorType = _value;
		}
		
		public function get sectorType():String
		{
			return m_sectorType;
		}
		
		public function set sectorName(_value:String):void
		{
			m_sectorName = _value;
		}
		
		public function get sectorName():String
		{
			return m_sectorName;
		}
		
		public function set oldSectorName(_value:String):void
		{
			m_oldSectorName = _value;
		}
		
		public function get oldSectorName():String
		{
			return m_oldSectorName;
		}
		
	}

}