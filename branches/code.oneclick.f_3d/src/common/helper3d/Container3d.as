package common.helper3d 
{
	import flash.geom.Vector3D;
	/**
	 * ...
	 * @author ...
	 */
	public class Container3d 
	{
		protected var m_position:Vector3D = new Vector3D();
		protected var m_rotation:Vector3D = new Vector3D();
		protected var m_parent:Container3d = null;
		
		public function set Parent(_value:Container3d):void
		{
			m_parent = _value;
		}
		
		public function get Parent():Container3d
		{
			return m_parent;
		}
		
		public function set Position(_value:Vector3D):void
		{
			m_position = _value;
		}
		
		public function get Position():Vector3D
		{
			return m_position;
		}
		
		public function set Rotation(_value:Vector3D):void
		{
			m_rotation = _value;
		}
		
		public function get Rotation():Vector3D
		{
			return m_rotation;
		}
		
		public function Container3d() 
		{
			
		}
		
	}

}