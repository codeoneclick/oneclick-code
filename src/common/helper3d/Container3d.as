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