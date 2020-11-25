// https://m.blog.naver.com/manhdh/220038243469
< Torrent 원리 정리 >

[용어]---------------------------------------------------------------------------------------------------------------------------------------------------
Piece:
파일의 1개의 조각
(토렌트는 하나의 파일을 여러 조각으로 나누고, 조각단위로 공유함)
(토렌트에서 조각의 크기를 설정할 수 있음)

Peer {
	Seeder:
	파일의 '모든' 조각을 가지고 있는 클라이언트

	Leecher:
	파일의 '일부' 조각을 가지고 있는 클라이언트
}

Tracker:
파일 공유를 위해 Peer들의 정보를 가지고 있는 서버.
(토렌트 파일마다 Tracker를 여러개 가지고 있을 수 있으며, 피어들이 많을수록 속도가 높다)

Swarm:
파일마다의 Hash(고유식별자) 정보와 Peer리스트의 정보 모음. (즉, 현재 파일을 공유하고 있다고 Tracker서버에 등록되어 있는 Peer의 목록을 의미)
Tracker가 가지고 있다.
(이를 기반으로 Tracker에게 접속하는 클라이언트들에게 Peer 목록을 전송해준다.)


[사전 지식]---------------------------------------------------------------------------------------------------------------------------------------------
Torrent File:
토렌트에 대한 기본 정보를 가지고 있는 메타 파일.

파일 구조:
Torrent {
	File name:
	토렌트 파일 이름(sampleName.torrent)
	
	Info Hash:
	공유하는 파일의 고유한 Hash 값
}

Tracker {
	Tracker URL:
	Tracker의 주소. 여러개 포함 가능
	
	Directory:
	토렌트파일이 저장되는 디렉토리 이름
}

Meta Data {
	Created On:
	생성 일자 시간
	
	Created By:
	생성자 정보
	
	Comment:
	생성자가 작성할 설명
}

Files {
	Piece Length:
	공유에 사용할 파일 조각의 크기
	
	File name:
	공유하는 실제 파일 이름
}

[동작 절차]-----------------------------------------------------------------------------------------------------------------------------------------------
1. 토렌트 시작
토렌트 파일을 실행해 클라이언트에 등록한다. 
토렌트 파일에 명시된 Tracker들에게 접속 시도한다.

2. Tracker Request (Peer와 Tracker 간 통신 - Tracker Request (Http 프로토콜 이용))
클라이언트가 Tracker에게 내 정보(IP,Port...), 파일 Hash값과 본인의 Peer 정보를 전송. (해당 토렌토의 피어 목록을 얻기 위해서)
클라이언트가 Tracker에게 요청할때 보내는 데이터들 {
	info_hash:
	토렌트 파일에 포함된 공유 파일의 Hash 정보 

	peer_id:
	클라이언트를 식별하기 위한 ID 

	port:
	Tracker Response 메시지에서 사용되는 클라이언트 TCP/UDP port 

	upload:
	클라이언트가 업로드한 공유 파일의 총계 (byte) 

	download:
	클라이언트가 다운로드한 공유 파일의 총계 (byte)

	left:
	다운로드 받을 파일의 남은 크기 (byte) 

	key (option):
	클라이언트 IP 주소가 변경되더라도 클라이언트를 인식할 수 있는 비공개 값 (peer 들간에 공유 되지 않음) 

	numwant (option):
	몇 개의 Peer 들의 정볼르 받을 것인지 요청 (기본 50) 

	compact: 
	Set 1: Peer 들의 IP주소와 Port 정보 만을 받음
	Set 2: IP 주소와 Port 외에 Peer-ID 등의 정보를 받음

	no_peer_id:
	Peer-ID는 생략하고 정보를 요청 (compact = 1 경우 무시) 

	event:
	Started - 파일 전송 시작 상태
	Stopped - 파일 전송 중지 상태
	Completed - 파일 전송 완료 상태

	ip (option):
	클라이언트의 IP 주소
}

3. Swarm 검색 및 생성 (Peer와 Tracker 간 통신 -  Tracker Response (Http 프로토콜 이용))
Peer로부터 받은 Hash 검색
랜덤으로 기본 50개의 피어를 선정하여 전송 준비
만약 Swarm이 없다면 생성

Tracker Request를 받은 Tracker는 해당 토렌트의 Hash값을 참조하여, Swarm이 존재하는지 검색한다.
Swarm이 존재한다면 Swarm이 포함된 Peer들을 목록으로 만들어 클라이언트에게 전송한다.

