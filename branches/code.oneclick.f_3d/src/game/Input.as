package game 
{
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class Input 
	{
		
		private var m_mouseDown:Boolean = false;
		private var m_oldMousePos:Point = new Point();
		private var m_mouseDragOffset:Point = new Point();
		
		public function get mousePosition():Point
		{
			return m_oldMousePos;
		}
		
		public function get dragMouseOffset():Point
		{
			return m_mouseDragOffset;
		}
		
		public function get mouseDown():Boolean
		{
			return m_mouseDown;
		}
		
		public function Input() 
		{
			init();
		}
		
		private function init():void
		{
			Core.stage.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Core.stage.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Core.stage.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
		}
		
		private function onMouseDown(_event:MouseEvent):void
		{
			m_mouseDown = true;
		}
		
		private function onMouseUp(_event:MouseEvent):void
		{
			m_mouseDown = false;
		}
		
		private function onMouseMove(_event:MouseEvent):void
		{
			if (m_mouseDown)
			{
				m_mouseDragOffset.x = m_oldMousePos.x - _event.localX;
				m_mouseDragOffset.y = m_oldMousePos.y - _event.localY;
			
				if (m_mouseDragOffset.x != 0)
					Core.camera.Position.x -= m_mouseDragOffset.x;
				
				if (m_mouseDragOffset.y != 0)
					Core.camera.Position.z += m_mouseDragOffset.y;
			}
				
			m_oldMousePos.x = _event.localX;
			m_oldMousePos.y = _event.localY;
		}
		
	}

}