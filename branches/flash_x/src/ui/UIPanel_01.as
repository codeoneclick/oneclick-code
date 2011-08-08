package ui 
{
	import core.Global;
	import fl.containers.ScrollPane;
	import fl.controls.Button;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.FileReference;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UIPanel_01 extends UIPanel
	{
		
		private var m_saveButton:Button = new Button();
		private var m_loadButton:Button = new Button();
		
		private var m_fileReference:FileReference = null;
		
		public function UIPanel_01() 
		{
			super();
			init();
		}
		
		private function init():void
		{
			m_saveButton.label = "save";
			m_saveButton.x = 10;
			m_saveButton.y = 70;
			m_saveButton.width = UISetting.k_PANEL_WIDTH - 20;
			m_saveButton.addEventListener(MouseEvent.CLICK, onSaveBtnClick);
						
			m_loadButton.label = "load";
			m_loadButton.x = 10;
			m_loadButton.y = 100;
			m_loadButton.width = UISetting.k_PANEL_WIDTH - 20;
			m_loadButton.addEventListener(MouseEvent.CLICK, onLoadBtnClick);
			
			m_plane.addChild(m_saveButton);
			m_plane.addChild(m_loadButton);
		}
		
		private function onSaveBtnClick(_event:MouseEvent):void
		{
			m_fileReference = new FileReference();
            m_fileReference.addEventListener(Event.SELECT, onFileOutSave);
            m_fileReference.addEventListener(Event.CANCEL, onFileOutCancel);
			m_fileReference.save(Global.sceneController.SaveMapData(), "mapdata.data");
		}
		
		private function onLoadBtnClick(_event:MouseEvent):void
		{
			m_fileReference = new FileReference();
            m_fileReference.addEventListener(Event.SELECT, onFileInBrowse);
            m_fileReference.addEventListener(Event.CANCEL, onFileInCancel);
			m_fileReference.browse();
		}
		
		private function onFileOutSave(_event:Event):void
		{
			
		}
		
		private function onFileOutCancel(_event:Event):void
		{
			
		}
		
		private function onFileInBrowse(_event:Event):void
		{
			m_fileReference.addEventListener(Event.COMPLETE, onFileLoaded);
			m_fileReference.load();
		}
		
		private function onFileInCancel(_event:Event):void
		{
			
		}
		
		private function onFileLoaded(_event:Event):void
		{
			Global.sceneController.ClearMapData();
			Global.sceneController.LoadMapData(_event.target.data);
		}
	}
}