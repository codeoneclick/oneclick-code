package ui 
{
	import core.Global;
	import fl.controls.ScrollBarDirection;
	import fl.controls.TileList;
	import flash.events.Event;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UIController
	{	
		private var m_preview:TileList = new TileList();
		
		public function UIController() 
		{
			Global.uiContainer.addChild(m_preview);
			m_preview.width = Global.setting.windowWidth;
			m_preview.height = 64;
			m_preview.x = 0;
			m_preview.y = Global.setting.windowHeight - m_preview.height;
			m_preview.columnWidth = 64;
			m_preview.rowHeight = 64;
			m_preview.direction = ScrollBarDirection.HORIZONTAL;
			m_preview.addItem( { label:"", source:"content/tile_00.png" } );
			m_preview.addItem( { label:"", source:"content/tile_01.png" } );	
			m_preview.addItem( { label:"", source:"content/tile_02.png" } );	
			m_preview.addItem( { label:"", source:"content/tile_03.png" } );	
			m_preview.addItem( { label:"", source:"content/tile_04.png" } );	
			m_preview.addEventListener(Event.CHANGE, onPreviewItemChange);
		}
		
		private function onPreviewItemChange(_event:Event):void
		{
			Global.editorController.previewSelectedIndex = (_event.target as TileList).selectedIndex;
		}

	}

}