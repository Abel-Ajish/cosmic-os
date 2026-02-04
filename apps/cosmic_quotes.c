#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *quotes[] = {
    "Your word is a lamp to my feet and a light to my path. - Psalm 119:105",
    "I can do all things through him who strengthens me. - Philippians 4:13",
    "Trust in the Lord with all your heart. - Proverbs 3:5",
    "You are the light of the world. - Matthew 5:14",
    "Rejoice in hope, be patient in tribulation, be constant in prayer. - Romans 12:12",
    "Be still, and know that I am God. - Psalm 46:10",
    "My soul finds rest in God alone. - Psalm 62:1",
    "You will keep in perfect peace those whose minds are steadfast. - Isaiah 26:3",
    "Above all else, guard your heart. - Proverbs 4:23",
    "I am the bread of life. - John 6:35",
    "My help comes from the Lord. - Psalm 121:2",
    "Blessed are the peacemakers. - Matthew 5:9",
    "Cast your cares on the Lord. - Psalm 55:22",
    "If you declare with your mouth, 'Jesus is Lord,' you will be saved. - Romans 10:9",
    "My grace is sufficient for you. - 2 Corinthians 12:9",
    "For I know the plans I have for you. - Jeremiah 29:11",
    "Rejoice always. - 1 Thessalonians 5:16",
    "In the beginning, God created the heavens and the earth. - Genesis 1:1",
    "Fear not, for I am with you; be not dismayed, for I am your God. - Isaiah 41:10",
    "God is love. - 1 John 4:8",
    "Jesus wept. - John 11:35",
    "The fruit of the Spirit is love, joy, peace, patience, kindness. - Galatians 5:22",
    "Let all that you do be done in love. - 1 Corinthians 16:14",
    "For we walk by faith, not by sight. - 2 Corinthians 5:7",
    "The Lord is my shepherd, I shall not want. - Psalm 23:1",
    "Ask, and it will be given you; search, and you will find. - Matthew 7:7",
    "The truth will make you free. - John 8:32",
    "Everything has its time. - Ecclesiastes 3:1",
    "A soft answer turns away wrath. - Proverbs 15:1",
    "Faith is the assurance of things hoped for. - Hebrews 11:1"
};

int main() {
    srand(time(NULL));
    int index = rand() % (sizeof(quotes) / sizeof(quotes[0]));
    
    printf("\033[1;35m📖 Cosmic Quotes (NRSV):\033[0m\n");
    printf("\033[1;33m\"%s\"\033[0m\n", quotes[index]);
    
    return 0;
}
