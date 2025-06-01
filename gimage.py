from icrawler.builtin import GoogleImageCrawler

def download_images(keyword, max_num=10):
    crawler = GoogleImageCrawler(storage={'root_dir': keyword})
    crawler.crawl(keyword=keyword, max_num=max_num)

if __name__ == "__main__":
    keyword = input("Enter search keyword(s): ")
    max_images = int(input("How many images to download? "))
    download_images(keyword, max_images)