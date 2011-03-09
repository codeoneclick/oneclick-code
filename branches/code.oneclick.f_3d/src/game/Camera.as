package game 
{
	import flash.events.Event;
	import flash.geom.Vector3D;
	/**
	 * ...
	 * @author ...
	 */
	public class Camera 
	{
		private var m_position:Vector3D = new Vector3D();
		private var m_rotation:Vector3D = new Vector3D();
		private var m_screenWidth:int = 800;
		private var m_screenHeight:int = 600;
		
		private var m_fovRatio:Number = 1;
		
		private var m_offsetMax:Vector3D = new Vector3D();
		private var m_offsetMin:Vector3D = new Vector3D();
		
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
		
		public function get ScreenWidth():int
		{
			return m_screenWidth;
		}
		
		public function get ScreenHeight():int
		{
			return m_screenHeight;
		}
		
		public function get AspectRatio():Number
		{
			return m_screenWidth / m_screenHeight;
		}
		
		public function get Fov():Number
		{
			return m_fovRatio;
		}
		
		public function Camera() 
		{
			init();
		}
		
		private function init():void
		{
			m_offsetMax.x = 512;
			m_offsetMax.z = 768;
			
			m_offsetMin.x = -1024;
			m_offsetMin.z = 128;
			Core.stage.addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function update(_event:Event):void
		{
			if (m_position.z < m_offsetMin.z )
				m_position.z = m_offsetMin.z;
				
			if (m_position.z > m_offsetMax.z )
				m_position.z = m_offsetMax.z;
				
			if (m_position.x > m_offsetMax.x)
				m_position.x = m_offsetMax.x;
				
			if (m_position.x < m_offsetMin.x)
				m_position.x = m_offsetMin.x;
				
			m_position.y = -200;
		}
		
	}

}