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
		private var m_panelList:Vector.<UIPanel> = new Vector.<UIPanel>();
		private var m_bookmarkList:Vector.<Button> = new Vector.<Button>();

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
					Global.editorController.pickBookmarkName = i;
				}
			}
		}
	}
}