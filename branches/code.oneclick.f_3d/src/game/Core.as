package game 
{
	import common.loader.BitmapLoader;
	/**
	 * ...
	 * @author ...
	 */
	public class Core 
	{
		
		public static const k_CONTENT_PATH:String = "Content/";
		
		private static var m_bitmapLoader:BitmapLoader = null;
		
		public static function get bitmapLoader():BitmapLoader
		{
			if (m_bitmapLoader == null)
			{
				m_bitmapLoader = new BitmapLoader();
			}
			
			return m_bitmapLoader;
		}
	}

}