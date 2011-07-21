package ui 
{
	import adobe.utils.CustomActions;
	import core.Global;
	import fl.containers.ScrollPane;
	import fl.controls.Button;
	import fl.controls.ScrollBarDirection;
	import fl.controls.TileList;
	import fl.controls.UIScrollBar;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.FileReference;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UIController
	{	
		//private var m_panel_01:UIPanel_01 = null;
		
		private var m_panelList:Vector.<UIPanel> = new Vector.<UIPanel>();
		private var m_bookmarkList:Vector.<Button> = new Vector.<Button>();
		
		/*private static const k_LAYER_TILE:String = "LAYER_TILE";
		private static const k_LAYER_OBJECT:String = "LAYER_OBJECT";
		
		private var m_previewList:Dictionary = new Dictionary();
		
		private var m_saveButton:Button = new Button();
		private var m_loadButton:Button = new Button();
		
		private var m_fileReference:FileReference = null;*/
		
		public function UIController() 
		{
			m_panelList.push(new UIPanel_01());
			m_panelList[0].name = "1";
			
			m_panelList.push(new UIPanel_02());
			m_panelList[1].name = "2";
			m_panelList[1].visible = false;
			
			m_panelList.push(new UIPanel_03());
			m_panelList[2].name = "3";
			m_panelList[2].visible = false;
			
			m_panelList.push(new UIPanel_04());
			m_panelList[3].name = "4";
			m_panelList[3].visible = false;
			
			m_bookmarkList.push(new Button());
			m_bookmarkList[0].width = UISetting.k_BOOKMARK_WIDTH;
			m_bookmarkList[0].height = UISetting.k_BOOKMARK_HEIGHT;
			m_bookmarkList[0].y = UISetting.k_BOOKMARK_OFFSET;
			m_bookmarkList[0].x = Global.setting.windowWidth - UISetting.k_PANEL_WIDTH + UISetting.k_BOOKMARK_OFFSET;
			m_bookmarkList[0].label = "1";
			
			m_bookmarkList.push(new Button());
			m_bookmarkList[1].width = UISetting.k_BOOKMARK_WIDTH;
			m_bookmarkList[1].height = UISetting.k_BOOKMARK_HEIGHT;
			m_bookmarkList[1].y = UISetting.k_BOOKMARK_OFFSET;
			m_bookmarkList[1].x = Global.setting.windowWidth - UISetting.k_PANEL_WIDTH + UISetting.k_BOOKMARK_OFFSET * 2 + UISetting.k_BOOKMARK_WIDTH;
			m_bookmarkList[1].label = "2";

			
			m_bookmarkList.push(new Button());
			m_bookmarkList[2].width = UISetting.k_BOOKMARK_WIDTH;
			m_bookmarkList[2].height = UISetting.k_BOOKMARK_HEIGHT;
			m_bookmarkList[2].y = UISetting.k_BOOKMARK_OFFSET;
			m_bookmarkList[2].x = Global.setting.windowWidth - UISetting.k_PANEL_WIDTH + UISetting.k_BOOKMARK_OFFSET * 3 + UISetting.k_BOOKMARK_WIDTH * 2;
			m_bookmarkList[2].label = "3";
			
			m_bookmarkList.push(new Button());
			m_bookmarkList[3].width = UISetting.k_BOOKMARK_WIDTH;
			m_bookmarkList[3].height = UISetting.k_BOOKMARK_HEIGHT;
			m_bookmarkList[3].y = UISetting.k_BOOKMARK_OFFSET;
			m_bookmarkList[3].x = Global.setting.windowWidth - UISetting.k_PANEL_WIDTH + UISetting.k_BOOKMARK_OFFSET * 4 + UISetting.k_BOOKMARK_WIDTH * 3;
			m_bookmarkList[3].label = "4";

			
			for ( var i:int = 0; i < m_bookmarkList.length; i++ )
			{
				m_bookmarkList[i].addEventListener(MouseEvent.CLICK, onBookmarkClick);
				Global.uiContainer.addChild(m_bookmarkList[i]);
			}
			
			
			/*m_previewList[k_LAYER_TILE] = new TileList();
	
			Global.uiContainer.addChild(m_previewList[k_LAYER_TILE]);
			
			m_previewList[k_LAYER_TILE].width = Global.setting.windowWidth;
			m_previewList[k_LAYER_TILE].height = 64;
			m_previewList[k_LAYER_TILE].x = 0;
			m_previewList[k_LAYER_TILE].y = Global.setting.windowHeight - m_previewList[k_LAYER_TILE].height;
			m_previewList[k_LAYER_TILE].columnWidth = 64;
			m_previewList[k_LAYER_TILE].rowHeight = 64;
			m_previewList[k_LAYER_TILE].direction = ScrollBarDirection.HORIZONTAL;
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/sector_00.png" } );
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/sector_01.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/sector_02.png" } );	
			m_previewList[k_LAYER_TILE].addItem( { label:"", source:"content/sector_03.png" } );	
			m_previewList[k_LAYER_TILE].addEventListener(Event.CHANGE, onPreviewItemChange);
			
			m_saveButton.label = "save";
			m_saveButton.x = 10;
			m_saveButton.y = 20;
			m_saveButton.addEventListener(MouseEvent.CLICK, onSaveBtnClick);
			
			m_loadButton.label = "load";
			m_loadButton.x = 10;
			m_loadButton.y = 50;
			m_loadButton.addEventListener(MouseEvent.CLICK, onLoadBtnClick);
			
			Global.uiContainer.addChild(m_saveButton);
			Global.uiContainer.addChild(m_loadButton);
			
			var temp:ScrollPane = new ScrollPane();
			Global.uiContainer.addChild(temp);*/
		}
		
		private function onBookmarkClick(_event:MouseEvent):void
		{
			var name:String = (_event.target as Button).label;
			
			for ( var i:int = 0; i < m_panelList.length; i++ )
			{
				m_panelList[i].visible = false;
				
				if (m_panelList[i].name == name)
				{
					m_panelList[i].visible = true;
				}
			}
		}
		

		/*
		private function onPreviewItemChange(_event:Event):void
		{
			Global.editorController.previewSelectedIndex = (_event.target as TileList).selectedIndex;
		}*/

	}

}