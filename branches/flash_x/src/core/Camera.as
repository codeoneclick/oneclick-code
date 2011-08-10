package core 
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Camera 
	{
		public static const k_ZOOM:Array = new Array(1, 0.75, 0.5);
		private var m_position:Point = new Point(0, 0);
		private var m_zoomIndex:int = 0;
		
		public function Camera(){}
		
		public function set position(_value:Point):void
		{
			m_position = _value;
		}
		
		public function get position():Point
		{
			return m_position;
		}
		
		public function get zoomIndex():int
		{
			return m_zoomIndex;
		}
		
		public function zoomIn():Boolean
		{
			if (m_zoomIndex - 1 >= 0)
			{
				m_zoomIndex--;
				position = position.add(new Point(position.x * (k_ZOOM[m_zoomIndex] - Global.inGameContainer.scaleX),
												  position.y * (k_ZOOM[m_zoomIndex] - Global.inGameContainer.scaleY)));
				Global.sceneController.visualLayers.scaleX = k_ZOOM[m_zoomIndex];
				Global.sceneController.visualLayers.scaleY = k_ZOOM[m_zoomIndex];				
				return true;
			}
			else
			{
				return false;
			}
		}
		
		public function zoomOut():Boolean
		{
			if (m_zoomIndex + 1 < k_ZOOM.length)
			{
				m_zoomIndex++;
				position = position.add(new Point(position.x * (Global.inGameContainer.scaleX - k_ZOOM[m_zoomIndex]),
												  position.y * (Global.inGameContainer.scaleY - k_ZOOM[m_zoomIndex])));
				Global.sceneController.visualLayers.scaleX = k_ZOOM[m_zoomIndex];
				Global.sceneController.visualLayers.scaleY = k_ZOOM[m_zoomIndex];				
				return true;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}