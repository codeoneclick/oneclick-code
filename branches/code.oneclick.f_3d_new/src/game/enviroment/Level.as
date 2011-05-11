package game.enviroment 
{
	import common.helper3d.Container3d;
	import common.helper3d.Sprite3d;
	import common.ui.UIControl;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	import game.core.Core;
	import game.enviroment.Building;
	import game.enviroment.GroundCell;
	import game.ui.MainMenu;
	/**
	 * ...
	 * @author ...
	 */
	public class Level 
	{
		public static const k_MAP_WIDTH:int  = 12;
		public static const k_MAP_HEIGHT:int = 12;
		public static const k_DECO_OFFSET:int = 2;
		
		public static const k_STATE_ROTATION_NONE:int = 0;
		public static const k_STATE_ROTATION_LEFT:int = 1;
		public static const k_STATE_ROTATION_RIGHT:int = 2;
		public static const k_STATE_ROTATION_UP:int = 3;
		public static const k_STATE_ROTATION_DOWN:int = 4;
		
		private static const k_MAX_ANGLE_OFFSET:Number = 0.77;
		
		private var m_mapContainer:Container3d = new Container3d();
		
		private var m_groundCellsList:Vector.<GroundCell>  = new Vector.<GroundCell>();
		private var m_decoCellsList:Vector.<DecoCell> = new Vector.<DecoCell>();
		private var m_characterCellsList:Vector.<CharacterCell> = new Vector.<CharacterCell>();
		
		private var m_enviromentCellsList:Vector.<GameNode> = new Vector.<GameNode>();
		
		private var m_zOrderSortingNodes:Vector.<GameNode> = new Vector.<GameNode>();
		
		private var m_zOrderSortLayer:Sprite = new Sprite();
		private var m_zOrderNoSortLayer:Sprite = new Sprite();
		
		private var m_characterPreviewCell:CharacterCell = null;
		
		private var m_rotationState:int = 0;
		private var m_rotationY:Number = 0.0;
		private var m_rotationX:Number = 0.0;
		
		private static var i:int = 0;
		private static var j:int = 0;
		
		public function Level() 
		{
			init();
		}
		
		private function init():void
		{
			Core.displayContainer.addChild(m_zOrderNoSortLayer);
			Core.displayContainer.addChild(m_zOrderSortLayer);
			
			var workingGroundCell:GroundCell = null;
			var workingDecoCell:DecoCell = null;
			var workingCharacterCell:CharacterCell = null;
			
			for ( i = 0; i < k_MAP_WIDTH; i++)
			{
				for ( j = 0; j < k_MAP_HEIGHT; j++)
				{
					workingGroundCell = new GroundCell(m_zOrderNoSortLayer, new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), new Point(i, j), "island", onLogicEventCallback);
					workingGroundCell.Parent = m_mapContainer;
					workingGroundCell.Rotation.x = 1.57;
					workingGroundCell.Position.x = GroundCell.k_WIDTH * i - GroundCell.k_WIDTH * (k_MAP_WIDTH  - 1) / 2;
					workingGroundCell.Position.z = GroundCell.k_HEIGHT * j - GroundCell.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2;
					m_groundCellsList.push(workingGroundCell);
					
					if (i < k_DECO_OFFSET || j < k_DECO_OFFSET || i >= (k_MAP_WIDTH - k_DECO_OFFSET) || j >= (k_MAP_HEIGHT - k_DECO_OFFSET))
					{
						workingGroundCell.filled = true;
						
						workingDecoCell = new DecoCell(m_zOrderSortLayer, new Point(GroundCell.k_WIDTH / 2, GroundCell.k_HEIGHT / 2), "deco_cell_pic");
						workingDecoCell.Parent = m_mapContainer;
						workingDecoCell.Rotation.y = 0;
						workingDecoCell.Position.x = GroundCell.k_WIDTH * i - GroundCell.k_WIDTH * (k_MAP_WIDTH  - 1) / 2;
						workingDecoCell.Position.z = GroundCell.k_HEIGHT * j - GroundCell.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2;
						workingDecoCell.Position.y = GroundCell.k_WIDTH / 4;
						m_enviromentCellsList.push(workingDecoCell);
						m_decoCellsList.push(workingDecoCell);
						m_zOrderSortingNodes.push(workingDecoCell);
					}
					else
					{
						/*workingCharacterCell = new CharacterCell(m_zOrderSortLayer, new Point(GroundCell.k_WIDTH / 2 , GroundCell.k_HEIGHT ), "character_cell_pic", onLogicEventCallback);
						workingCharacterCell.Parent = m_mapContainer;
						workingCharacterCell.Rotation.y = 0;
						workingCharacterCell.Position.x = GroundCell.k_WIDTH * i - GroundCell.k_WIDTH * (k_MAP_WIDTH  - 1) / 2;
						workingCharacterCell.Position.z = GroundCell.k_HEIGHT * j - GroundCell.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2;
						workingCharacterCell.Position.y = GroundCell.k_WIDTH / 2;
						m_enviromentCellsList.push(workingCharacterCell);
						m_characterCellsList.push(workingCharacterCell);
						m_zOrderSortingNodes.push(workingCharacterCell);*/
					}
				}
			}			
			
			Core.stage.addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function update(_event:Event):void
		{
			m_mapContainer.Position = Core.camera.Position;
			m_mapContainer.Rotation.y = m_rotationY;
			m_mapContainer.Rotation.x = m_rotationX;
			
			switch(m_rotationState)
			{
				case k_STATE_ROTATION_LEFT :
				{
					if (m_rotationY > -k_MAX_ANGLE_OFFSET)
					{
						m_rotationY -= 0.0285;
						MainMenu.background.x += 3;
					}
					
				}
				break;
				
				case k_STATE_ROTATION_RIGHT :
				{
					if (m_rotationY < k_MAX_ANGLE_OFFSET)
					{
						m_rotationY += 0.0285;
						MainMenu.background.x -= 3;
					}
				}
				break;
				
				case k_STATE_ROTATION_DOWN :
				{
					if(m_rotationX > 0)
						m_rotationX -= 0.0285;
				}
				break;
				
				case k_STATE_ROTATION_UP :
				{
					if(m_rotationX < k_MAX_ANGLE_OFFSET)
						m_rotationX += 0.0285;
				}
				break;
			}
			
			zOrder();
		}
		
		private function onLogicEventCallback(_node:GameNode, _eventId:int):void
		{
			if ( _node is CharacterCell)
			{
				var index:int = 0;
				
				switch(_eventId)
				{
					case CharacterCell.k_MOUSE_OVER :
					{
						index = m_enviromentCellsList.indexOf(_node, 0);
						
						if (m_enviromentCellsList[index + 1] != null)
							m_enviromentCellsList[index + 1].alpha = 0.5;
						
						if (m_enviromentCellsList[index + 1] != null)
							m_enviromentCellsList[index + 1].alpha = 0.5;
						
						if (m_enviromentCellsList[index + 1 + k_MAP_WIDTH] != null)	
							m_enviromentCellsList[index + 1 + k_MAP_WIDTH].alpha = 0.5;
						
						if (m_enviromentCellsList[index - 1 + k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - 1 + k_MAP_WIDTH].alpha = 0.5;
						
						if (m_enviromentCellsList[index  + k_MAP_WIDTH] != null)
							m_enviromentCellsList[index  + k_MAP_WIDTH].alpha = 0.5;
						
						if ((index + 1 - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index + 1 - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index + 1 - k_MAP_WIDTH].alpha = 0.5;
						
						if ((index - 1 - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index - 1 - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - 1 - k_MAP_WIDTH].alpha = 0.5;
						
						if ((index - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - k_MAP_WIDTH].alpha = 0.5;
					}
					break;
					
					case CharacterCell.k_MOUSE_OUT :
					{
						index = m_enviromentCellsList.indexOf(_node, 0);
						if (m_enviromentCellsList[index + 1] != null)
							m_enviromentCellsList[index + 1].alpha = 1.0;
						
						if (m_enviromentCellsList[index + 1] != null)
							m_enviromentCellsList[index + 1].alpha = 1.0;
						
						if (m_enviromentCellsList[index + 1 + k_MAP_WIDTH] != null)	
							m_enviromentCellsList[index + 1 + k_MAP_WIDTH].alpha = 1.0;
						
						if (m_enviromentCellsList[index - 1 + k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - 1 + k_MAP_WIDTH].alpha = 1.0;
						
						if (m_enviromentCellsList[index  + k_MAP_WIDTH] != null)
							m_enviromentCellsList[index  + k_MAP_WIDTH].alpha = 1.0;
						
						if ((index + 1 - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index + 1 - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index + 1 - k_MAP_WIDTH].alpha = 1.0;
						
						if ((index - 1 - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index - 1 - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - 1 - k_MAP_WIDTH].alpha = 1.0;
						
						if ((index - k_MAP_WIDTH) > 0 && m_enviromentCellsList[index - k_MAP_WIDTH] != null)
							m_enviromentCellsList[index - k_MAP_WIDTH].alpha = 1.0;
					}
					break;
					
					case CharacterCell.k_MOUSE_CLICK :
					{
						
					}
					break;
				}
			}
			else if ( _node is DecoCell )
			{
				
			}
			else if ( _node is GroundCell )
			{
				switch(_eventId)
				{
					case GroundCell.k_MOUSE_OVER :
					{
						if (m_characterPreviewCell != null)
						{
							if (!(_node as GroundCell).filled)
							{
								m_characterPreviewCell.Position.x = _node.Position.x;
								m_characterPreviewCell.Position.z = _node.Position.z;
								
								if ((_node as GroundCell).index.y <  k_MAP_HEIGHT / 2)
								{
									m_characterPreviewCell.highlight(CharacterCell.k_HIGHLIGHT_GREEN);
								}
								else
								{
									m_characterPreviewCell.highlight(CharacterCell.k_HIGHLIGHT_RED);
								}
							}
						}
					}
					break;
					
					case GroundCell.k_MOUSE_OUT :
					{
						
					}
					break;
				}
			}
		}
		
		public function onUIEventCallback(_control:UIControl, _eventId:int):void
		{
			if ( _control is MainMenu )
			{
				switch(_eventId)
				{
					case MainMenu.k_UI_BUTTON_LEFT_DOWN :
					{
						m_rotationState = k_STATE_ROTATION_LEFT;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_RIGHT_DOWN :
					{
						m_rotationState = k_STATE_ROTATION_RIGHT;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_LEFT_UP :
					{
						m_rotationState = k_STATE_ROTATION_NONE;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_RIGHT_UP :
					{
						m_rotationState = k_STATE_ROTATION_NONE;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_UP_UP :
					{
						m_rotationState = k_STATE_ROTATION_NONE;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_DOWN_UP :
					{
						m_rotationState = k_STATE_ROTATION_NONE;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_UP_DOWN :
					{
						m_rotationState = k_STATE_ROTATION_UP;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_DOWN_DOWN :
					{
						m_rotationState = k_STATE_ROTATION_DOWN;
					}
					break;
					
					case MainMenu.k_UI_BUTTON_CARD_01_CLICK :
					{
						onCreatePreview();
					}
					break;
				}
			}
		}
		
		private function onCreatePreview():void
		{
			if (m_characterPreviewCell == null)
			{	
				m_characterPreviewCell = new CharacterCell(m_zOrderSortLayer, new Point(GroundCell.k_WIDTH / 2 , GroundCell.k_HEIGHT ), "character_cell_pic", onLogicEventCallback);
				m_characterPreviewCell.Parent = m_mapContainer;
				m_characterPreviewCell.Rotation.y = 0;
				m_characterPreviewCell.Position.x = 0;
				m_characterPreviewCell.Position.z = 0;
				m_characterPreviewCell.Position.y = GroundCell.k_WIDTH / 2;
				m_characterPreviewCell.isIntersected = false;
				m_zOrderSortingNodes.push(m_characterPreviewCell);
				levelPlaceHighlight(true);
			}
			else
			{
				m_zOrderSortLayer.removeChild(m_characterPreviewCell as Sprite3d);
				m_zOrderSortingNodes.splice(m_zOrderSortingNodes.indexOf(m_characterPreviewCell, 0), 1);
				m_characterPreviewCell = null;
				levelPlaceHighlight(false);
			}
		}
		
		private function levelPlaceHighlight(_value:Boolean):void
		{
			var index:int = 0;
			for ( i = 0; i < k_MAP_WIDTH; i++)
			{
				for ( j = 0; j < k_MAP_HEIGHT; j++)
				{
					if (_value)
					{
						if(j < k_MAP_HEIGHT / 2 && !m_groundCellsList[index].filled)
							m_groundCellsList[index].highlight(GroundCell.k_HIGHLIGHT_GREEN);
						else if (m_groundCellsList[index].filled)
							m_groundCellsList[index].highlight(GroundCell.k_HIGHLIGHT_RED);
					}
					else
					{
						m_groundCellsList[index].highlight(GroundCell.k_HIGHLIGHT_NONE);
					}
					index++;
				}
			}
		}
		
		private function zOrder():void
		{
			m_zOrderSortingNodes.sort(Sprite3d.sprite3dSorter);
			for ( i = 0; i < m_zOrderSortingNodes.length; i++)
			{
				m_zOrderSortLayer.setChildIndex(m_zOrderSortingNodes[i], i);
				m_zOrderSortingNodes[i].Rotation.y = -m_rotationY;
			}	
		}	
	}
}