Name:     SocialGame
Version:  0.9
Release:  1
Summary:  The Social Game from CrossWeb Enterprise
Group:    Applications/Internet
Vendor:   CrossWeb Enterprise
License:  Proprietary
URL:      http://wvm002.dei.isep.ipp.pt/SocialGame

%description
The social network that lets you play at the same time

%prep
rm -rf $RPM_BUILD_DIR/game
zcat $RPM_SOURCE_DIR/game.tar.gz | tar -xvf -
cd src

%build
make

%install
mkdir -p %{buildroot}/usr/share/SocialGame
cp SocialGame %{buildroot}/usr/share/SocialGame/SocialGame
chmod +x %{buildroot}/usr/share/SocialGame/SocialGame
cp BG001.wav %{buildroot}/usr/share/SocialGame/BG001.wav
cp hangman_floor_texture.jpeg %{buildroot}/usr/share/SocialGame/hangman_floor_texture.jpeg
cp maze_floor.jpg %{buildroot}/usr/share/SocialGame/maze_floor.jpg
cp maze_walls.jpg %{buildroot}/usr/share/SocialGame/maze_walls.jpg
cp tictactoe_texture.jpg %{buildroot}/usr/share/SocialGame/tictactoe_texture.jpg
cp languages %{buildroot}/usr/share/SocialGame/languages
cp english %{buildroot}/usr/share/SocialGame/english
cp portuguese %{buildroot}/usr/share/SocialGame/portuguese
mkdir -p "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images"
cp "Graphics/SkyBox Images/negx.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/negx.jpg"
cp "Graphics/SkyBox Images/negy.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/negy.jpg"
cp "Graphics/SkyBox Images/negz.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/negz.jpg"
cp "Graphics/SkyBox Images/posx.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/posx.jpg"
cp "Graphics/SkyBox Images/posy.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/posy.jpg"
cp "Graphics/SkyBox Images/posz.jpg" "%{buildroot}/usr/share/SocialGame/Graphics/SkyBox Images/posz.jpg"
mkdir -p %{buildroot}/usr/share/applications
cp SocialGame.desktop %{buildroot}/usr/share/applications/SocialGame.desktop
mkdir %{buildroot}/usr/bin
cp socialgame %{buildroot}/usr/bin/socialgame
chmod +x %{buildroot}/usr/bin/socialgame

%files
/usr/share/SocialGame/SocialGame
/usr/share/SocialGame/BG001.wav
/usr/share/SocialGame/hangman_floor_texture.jpeg
/usr/share/SocialGame/maze_floor.jpg
/usr/share/SocialGame/maze_walls.jpg
/usr/share/SocialGame/tictactoe_texture.jpg
/usr/share/SocialGame/languages
/usr/share/SocialGame/english
/usr/share/SocialGame/portuguese
"/usr/share/SocialGame/Graphics/SkyBox Images/negx.jpg"
"/usr/share/SocialGame/Graphics/SkyBox Images/negy.jpg"
"/usr/share/SocialGame/Graphics/SkyBox Images/negz.jpg"
"/usr/share/SocialGame/Graphics/SkyBox Images/posx.jpg"
"/usr/share/SocialGame/Graphics/SkyBox Images/posy.jpg"
"/usr/share/SocialGame/Graphics/SkyBox Images/posz.jpg"
/usr/share/applications/SocialGame.desktop
/usr/bin/socialgame