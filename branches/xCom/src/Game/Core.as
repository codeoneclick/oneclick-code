package Game 
{
	import common.content.ContentLoader;
	/**
	 * ...
	 * @author ...
	 */
	public class Core 
	{
		private static var m_contentLoader:ContentLoader = null;
		
		public static function get contentLoader():ContentLoader
		{
			if (m_contentLoader == null)
			{
				m_contentLoader = new ContentLoader();				
			}
			return m_contentLoader;
		}
		
	}

}