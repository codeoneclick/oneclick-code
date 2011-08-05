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
	public class UIPanel_03 extends UIPanel
	{
		protected var m_preview:TileList = null;
		
		public function UIPanel_03() 
		{
			super();
			init();
		}
		
		private function init():void
		{
			m_preview = new TileList();
			
			m_preview.width = UISetting.k_PREVIEW_WIDTH;
			m_preview.height = UISetting.k_PREVIEW_HEIGHT;
			m_preview.x = UISetting.k_PREVIEW_OFFSET;
			m_preview.y = 70;
			
			m_preview.columnWidth = UISetting.k_PREVIEW_WIDTH - 16;
			m_preview.rowHeight = UISetting.k_PREVIEW_WIDTH / 2;
			m_preview.direction = ScrollBarDirection.VERTICAL;
			
			m_preview.addItem( { label:"", source:"content/deco_00.png" } );
			m_preview.addItem( { label:"", source:"content/deco_01.png" } );
			m_preview.addItem( { label:"", source:"content/deco_02.png" } );
			m_preview.addItem( { label:"", source:"content/deco_03.png" } );
			m_preview.addItem( { label:"", source:"content/deco_04.png" } );
			m_preview.addItem( { label:"", source:"content/deco_05.png" } );

			m_preview.addEventListener(Event.CHANGE, onSelect);
			m_plane.addChild(m_preview);
		}
		
		private function onSelect(_event:Event):void
		{
			Global.editorController.pickDecoName = (_event.target as TileList).selectedIndex;
		}
		
	}

}