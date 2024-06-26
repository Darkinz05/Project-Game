
# Souls Lite
- Demo Game: https://drive.google.com/drive/folders/1tLLu-VD7AAYrsk0CF_Vzmhb-YG6pFszk?usp=drive_link
- Speedrun AA: https://youtu.be/ixLMCKP-cVI
- Link Github: https://github.com/Darkinz05/Project-Game

# Giới thiệu:
Chào mừng đến với thế giới của Souls Lite - nơi mà sự kiên nhẫn và kỹ năng sẽ được thử thách đến cực hạn. Trong trò chơi này, bạn sẽ bước vào một cuộc hành trình đầy cam go, với chỉ một thanh kiếm và sự nhanh nhẹn của mình, bạn sẽ phải tìm cách đánh bại những con Boss xấu xa để mang lại bình yên cho ngôi làng.

- [0. Cách tải game](#0-cách-tải-game)
- [1. Bắt đầu game](#1-bắt-đầu-game)
- [2. Các thành phần trong game](#2-các-thành-phần)
- [3. Cách chơi](#3-cách-chơi)
- [4. Chiến thắng và thất bại](#4-chiến-thắng-và-thất-bại)
- [Credits](#credit)

# 0. Cách tải game

**Bước 1:** Tại Repo này, Chọn Code -> Download Zip (192 MB). File khá lớn do bao gồm cả các thư viện SDL cần thiết.

**Bước 2:** Sử dụng phiên bản Code::Block 32 bit. Do thư viện SDL mình dùng là loại 32 bit.

**Bước 3:**
- Giải nén project vào 1 thư mục.
- Chạy Project.cbp trong thư mục đó.
- Build and run trong Code::Block (hoặc có thể thử chạy bằng Debug nếu không được).

**Bước 4:** Bắt đầu trò chơi.

# 1. Bắt đầu game

Bắt đầu trò chơi sẽ là menu như dưới hình:
- Play: Chuyển sang menu chọn Level
- Tutorial: Hướng dẫn cách chơi
- Achievements: Hệ thống thành tựu
- Reset: Làm mới tiến trình chơi
<div style="text-align: center;">

![image](Preview/menu.png)

</div>

Đây là Menu chọn level:
- Level 1: Khu vực tuyết, là lãnh địa của Frost Guardian.
- Level 2: Khu vực hang, là lãnh địa của Stone Golem. Level 2 ban đầu sẽ bị khóa, người chơi cần vượt qua level 1 để có thể mở khóa level 2.
<div style="text-align: center;">

![image](Preview/menu_select.png)

</div>


# 2. Các thành phần trong game

- Player ![image](Preview/player.png): nhân vật của bạn
- Boss Frost Guardian ![image](Preview/boss1.png): Boss 1, là một người tuyết khổng lồ sống một mình trong lều tuyết, tập gym hàng ngày nên có một cơ thể rất to.
- Boss Stone Golem ![image](Preview/boss2.png): Boss 2, là một thực thể năng lượng huyền bí bị giằng xé trong những mảnh vỡ thiên thạch.
- Ngoài ra, còn có những vật thể khác do Boss tạo ra để tấn công bạn. Hãy cẩn thận!
- Hệ thống thành tựu:

<div style="text-align: center;">

![image](Preview/menu_ach.png)

</div>

- Nút Home ![image](Preview/home.png): dùng để pause hoặc quay về menu.
- Nút Âm thanh ![image](Preview/sound.png): dùng để tắt/bật âm thanh
- Bố cục game cơ bản:
<div style="text-align: center;">

![image](Preview/preview.png)

</div>

<div style="text-align: center;">

![image](Preview/preview-2.png)

</div>
# 3. Cách chơi

Bạn có thể học cách chơi trong game thông qua Tutorial.

Sử dụng phím A để sang trái và phím D để sang phải. ![ezgif com-video-to-gif](Preview/A.gif) ![ezgif com-video-to-gif](Preview/D.gif)

Sử dụng phím W để nhảy. Giữ W để nhảy cao hơn. ![ezgif com-video-to-gif](Preview/W.gif)

Sử dụng phím J để đánh thường. ![ezgif com-video-to-gif](Preview/J.gif)

Phím K để lướt một đoạn. ![ezgif com-video-to-gif](Preview/K.gif)

Mục tiêu của bạn là đánh cho Boss về 0 máu và bạn sẽ dành chiến thắng. Ngược lại, nếu bạn hết máu bạn thua.

Dưới đây là đặc điểm của từng boss

**Boss 1**
- Frost Guardian sẽ có 3 cách tấn công chính:
    - Tìm kiếm và tung nắm đấm.![ezgif com-video-to-gif](preview/boss1-1.gif)
    - Đấm ra một đạn băng về phía bạn.![ezgif com-video-to-gif](preview/ice.gif)
    - Bắn 3 cột băng lên trời và nó sẽ rơi xuống đầu bạn.![ezgif com-video-to-gif](preview/boss1-3.gif)

**Boss 2**
- Stone Golem cũng có 3 cách tấn công chính:
    - Tạo xung điện trường gây sát thương quanh bản thân![ezgif com-video-to-gif](preview/boss2-1.gif)
    - Bay về một phía và bắn bàn tay hỏa tiễn về phía bạn. Lưu ý, bàn tay hỏa tiễn sau một đoạn sẽ quay ngược về vị trí cũ.![ezgif com-video-to-gif](preview/boss2-2.gif)
    - Bao bọc bản thân bằng lớp giáp kiên cố. Trong thời gian này, Stone Golem sẽ tạo rung chấn làm cho các lớp đá trong hang rơi xuống. Lưu ý, nếu bạn tấn công Stone Golem, hắn sẽ hồi máu.![ezgif com-video-to-gif](preview/boss2-3.gif)
- Đặc biệt, Stone Golem có 2 dạng. Hắn sẽ chuyển dạng sau khi mất đi nửa số sinh mệnh. Lúc này hắn sẽ vô cùng nguy hiểm.![ezgif com-video-to-gif](preview/boss2-x.gif)

# 4. Chiến thắng và thất bại
Đánh bại boss và thu thập linh hồn của chúng, bạn sẽ chiến thắng.
<div style="text-align: center;">

![image](Preview/win.png)

</div>

Nếu bạn hết máu, bạn sẽ thua.

<div style="text-align: center;">

![image](Preview/lose.png)

</div>

# Credits
### Về đồ họa của game:
- Player : https://rvros.itch.io/
- Boss 1 : https://chierit.itch.io/
- Boss 2 : https://darkpixel-kronovi.itch.io/
- Dummy  : https://elthen.itch.io/
- Hình nền được lấy từ các tựa game: Eldest Souls, Cuphead,...
- Các tileset cho map:

    - https://atari-boy.itch.io/snow-platform-pack
    - https://brullov.itch.io/oak-woods


Cảm ơn mọi người vì đã cung cấp những nguồn tài nguyên miễn phí và quý giá.
### Về nhạc nền:
- Menu : The Legend of Zelda (Main theme).
- Map 1: Hollow Knight's Nightmare King.
- Map 2: Hollow Knight's Sisters of Battle.
### Về source code:

Mình có tham khảo và sử dụng code của kênh Youtube: https://www.youtube.com/@PhatTrienPhanMem123AZ vào các file CommonFunc, BaseObject, Player, GameMap,... và học được cách xây dựng tương tác với Map cho Player.
Các file còn lại đều là mình tự code và phát triển.

- CommonFunc(.h/.cpp) : include các thư viện SDL2, define các constant, một vài struct.
- BaseObject(.h/.cpp) : tạo class BaseObject để xử lí các vấn đề về phần hình ảnh cho cả image và ttf. Những class có hình ảnh sẽ đều được kế thừa từ BaseObject.
- Boss1(.h/.cpp) : tạo class Boss1. Trong này xử lí logic cho Boss1 bao gồm: di chuyển, hitbox, đạn bắn, hoạt ảnh, chuyển trạng thái, tương tác với Player/Map...
- Boss2(.h/.cpp) : tương tự như Boss1 nhưng vài phần xử lí sẽ khác.
- Bullet(.h/.cpp) : tạo class Bullet. Xử lí di chuyển của đạn, xóa đạn, vẽ đạn.
- Button(.h/.cpp) : tạo class Button. Làm các công việc xử lí event cho nút, vẽ nút.

- GameMap(.h/.cpp) : tạo class GameMap. Có chức năng vẽ map.

- Player(.h./.cpp) : tạo class Player. Xử lí logic cho player bao gồm: di chuyển, hitbox, hoạt ảnh, chuyển trạng, xử lí sự kiện, tương tác với các boss,
- Timer(.h/.cpp) : tạo class Timer. Chủ yếu để giới hạn fps.
- main.cpp: chứa xử lí chính của game.


