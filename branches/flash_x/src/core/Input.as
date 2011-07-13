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
			Global.stage.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Global.stage.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Global.stage.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
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
			Global.camera.offset = new Point(0, 0);
			
			if (m_isMouseDown)
			{
				m_mouseDragOffset.x = m_oldMousePos.x - _event.stageX;
				m_mouseDragOffset.y = m_oldMousePos.y - _event.stageY;
				
				Global.camera.offset = m_mouseDragOffset;
			
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