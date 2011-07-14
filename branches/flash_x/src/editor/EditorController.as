package editor 
{
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class EditorController 
	{
		private var m_previewSelectedIndex:int = 0;
		
		public function EditorController() 
		{
			
		}
		
		public function get previewSelectedIndex():int
		{
			return m_previewSelectedIndex;
		}
		
		public function set previewSelectedIndex(_value:int):void
		{
			m_previewSelectedIndex = _value;
		}
		
	}

}