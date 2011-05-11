package ui.common 
{
	import common.mvc.IView;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class IWindowView extends IView
	{
		
		public function IWindowView() 
		{
			init();
		}
		
		private function init():void
		{
			addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
		}
		
		private function onMouseMove(_event:MouseEvent):void
		{
			if (_event.buttonDown)
			{
				this.x = _event.stageX - this.width / 2;
				this.y = _event.stageY - this.height / 2;
			}
		}
		
	}

}