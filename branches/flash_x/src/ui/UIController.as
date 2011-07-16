package ui 
{
	import adobe.utils.CustomActions;
	import core.Global;
	import fl.controls.ScrollBarDirection;
	import fl.controls.TileList;
	import flash.events.Event;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UIController
	{	
		private static const k_LAYER_TILE:String = "LAYER_TILE";
		private static const k_LAYER_OBJECT:String = "LAYER_OBJECT";
		
		private var m_previewList:Dictionary = new Dictionary();
		
		public function UIController() 
		{
			
			m_previewList[k_LAYER_TILE] = new TileList();
			m_previewList[k_LAYER_OBJECT] = new TileList();
			
			Global.uiContainer.addChild(m_previewList[k_LAYER_TILE]);
			Global.uiContainer.addChild(m_previewList[k_LAYER_OBJECT]);
			
			m_previewList[k_LAYER_TILE].width = Global.setting.windowWidth;
			m_previewList[k_LAYER_TILE].height = 64;
			m_previewList[k_LAYER_TILE].x = 0;
			m_previewList[k_LAYER_TILE].y = Global.setting.windowHeight - m_previewList[k_LAYER_TILE].height;
			m_previewList[k_LAYER_TILE].columnWidth = 64;
			m_previewList[k_LAYER_TILE].rowHeight = 64;
			m_previewList[k_LAYER_TILE].direction = ScrollBarDirection.HORIZONTAL;
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_00.png" } );
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_01.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_02.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_03.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_04.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/tile_06.png" } );	
			m_previewList[k_LAYER_TILE].addEventListener(Event.CHANGE, onPreviewItemChange);
			
			m_previewList[k_LAYER_OBJECT].width = Global.setting.windowWidth;
			m_previewList[k_LAYER_OBJECT].height = 64;
			m_previewList[k_LAYER_OBJECT].x = 0;
			m_previewList[k_LAYER_OBJECT].y = Global.setting.windowHeight - m_previewList[k_LAYER_OBJECT].height * 2;
			m_previewList[k_LAYER_OBJECT].columnWidth = 64;
			m_previewList[k_LAYER_OBJECT].rowHeight = 64;
			m_previewList[k_LAYER_OBJECT].direction = ScrollBarDirection.HORIZONTAL;
			m_previewList[k_LAYER_OBJECT].addItem( { label:"", source:"content/tile_00.png" } );
			m_previewList[k_LAYER_OBJECT].addItem( { label:"", source:"content/tile_05.png" } );	
			m_previewList[k_LAYER_OBJECT].addEventListener(Event.CHANGE, onPreviewItemChange);
			
			
		}
		
		private function onPreviewItemChange(_event:Event):void
		{
			Global.editorController.previewSelectedIndex = (_event.target as TileList).selectedIndex;
		}

	}

}