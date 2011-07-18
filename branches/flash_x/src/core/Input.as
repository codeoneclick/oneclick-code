package core 
{
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Input 
	{
		private var m_isMouseDown:Boolean = false;
		private var m_oldMousePos:Point = new Point();
		private var m_mouseDragOffset:Point = new Point();
		
		public function Input() 
		{
			init();
		}
		
		private function init():void
		{
			Global.inGameContainer.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Global.inGameContainer.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Global.inGameContainer.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
			
			Global.backContainer.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Global.backContainer.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Global.backContainer.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
		}
		
		private function onMouseDown(_event:MouseEvent):void
		{
			m_isMouseDown = true;
		}
		
		private function onMouseUp(_event:MouseEvent):void
		{
			m_isMouseDown = false;
		}
		
		private function onMouseMove(_event:MouseEvent):void
		{	
			if (m_isMouseDown)
			{
				m_mouseDragOffset.x = m_oldMousePos.x - _event.stageX;
				m_mouseDragOffset.y = m_oldMousePos.y - _event.stageY;
				
				if (m_mouseDragOffset.x != 0)
					Global.camera.position.x += m_mouseDragOffset.x;
				
				if (m_mouseDragOffset.y != 0)
					Global.camera.position.y += m_mouseDragOffset.y;
			}

			m_oldMousePos.x = _event.stageX;
			m_oldMousePos.y = _event.stageY;
		}
		
	}

}